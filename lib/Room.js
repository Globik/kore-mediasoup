'use strict';

const EventEmitter = require('events').EventEmitter;
const logger = require('./logger')('Room');
const utils = require('./utils');
const errors = require('./errors');
const Peer = require('./Peer');

const KINDS = [ 'audio', 'video', 'depth' ];

class Room extends EventEmitter
{
	constructor(internal, data, channel)
	{
		logger.debug('constructor() [internal:%o, data:%o]', internal, data);

		super();
		this.setMaxListeners(Infinity);

		// Store internal data.
		// - .roomId
		this._internal = internal;

		// Channel instance.
		this._channel = channel;

		// RTP capabilities splitted into supported kinds.
		this._capabilities = {};

		// Map of Peer instances indexed by `peerName`.
		this._peers = new Map();

		// Map of RtpReceiver instances indexed by `rtpReceiverId`.
		this._rtpReceivers = new Map();

		// Closed flag.
		this._closed = false;

		// Subscribe to notifications.
		this._channel.on(this._internal.roomId, (event, data) =>
		{
			switch (event)
			{
				case 'close':
				{
					this.close(undefined, true);
					break;
				}

				case 'audiolevels':
				{
					let entries = data.entries;
					let data2 = [];

					for (let entry of entries)
					{
						let rtpReceiverId = entry[0];
						let audioLevel = entry[1];
						let rtpReceiver = this._rtpReceivers.get(rtpReceiverId);

						if (!rtpReceiver)
							continue;

						let peer = rtpReceiver.peer;

						if (!peer)
							continue;

						data2.push({ peer, rtpReceiver, audioLevel });
					}

					let orderedEntries = data2.sort((a, b) =>
					{
						if (a.audioLevel > b.audioLevel)
							return -1;
						else if (a.audioLevel < b.audioLevel)
							return 1;
						else
							return 0;
					});

					this.emit('audiolevels', orderedEntries);

					break;
				}

				default:
					logger.error('ignoring unknown event "%s"', event);
			}
		});

		// Subscribe to new events.
		this.on('newListener', (event) =>
		{
			switch (event)
			{
				case 'audiolevels':
				{
					// Ignore if there are listeners already.
					if (this.listenerCount('audiolevels'))
						return;

					// Send Channel request.
					this._channel.request('room.setAudioLevelsEvent', this._internal, { enabled: true })
						.then(() =>
						{
							logger.debug('"room.setAudioLevelsEvent" request succeeded');
						})
						.catch((error) =>
						{
							logger.error('"room.setAudioLevelsEvent" request failed: %s', error);
						});

					break;
				}
			}
		});

		// Subscribe to events removal.
		this.on('removeListener', (event) =>
		{
			switch (event)
			{
				case 'audiolevels':
				{
					// Ignore if there are other remaining listeners.
					if (this.listenerCount('audiolevels'))
						return;

					// Send Channel request.
					this._channel.request('room.setAudioLevelsEvent', this._internal, { enabled: false })
						.then(() =>
						{
							logger.debug('"room.setAudioLevelsEvent" request succeeded');
						})
						.catch((error) =>
						{
							logger.error('"room.setAudioLevelsEvent" request failed: %s', error);
						});

					break;
				}
			}
		});

		// Set room's capabilities.
		this._setCapabilities(data.capabilities);
	}

	get id()
	{
		return this._internal.roomId;
	}

	get closed()
	{
		return this._closed;
	}

	/**
	 * Get an array with all the Peers.
	 *
	 * @return {Array<Peer>}
	 */
	get peers()
	{
		return Array.from(this._peers.values());
	}

	/**
	 * Close the Room.
	 */
	close(error, dontSendChannel)
	{
		if (this._closed)
			return;

		this._closed = true;

		if (!error)
			logger.debug('close()');
		else
			logger.error('close() [error:%s]', error);

		// Remove notification subscriptions.
		this._channel.removeAllListeners(this._internal.roomId);

		// Close every Peer.
		for (let peer of this._peers.values())
		{
			peer.close(undefined, true);
		}

		if (!dontSendChannel)
		{
			// Send Channel request.
			this._channel.request('room.close', this._internal)
				.then(() =>
				{
					logger.debug('"room.close" request succeeded');
				})
				.catch((error) =>
				{
					logger.error('"room.close" request failed: %s', error);
				});
		}

		this.emit('close', error);
	}

	/**
	 * Dump the Room.
	 *
	 * @return {Promise}
	 */
	dump()
	{
		logger.debug('dump()');

		if (this._closed)
			return Promise.reject(new errors.InvalidStateError('Room closed'));

		return this._channel.request('room.dump', this._internal)
			.then((data) =>
			{
				logger.debug('"room.dump" request succeeded');

				return data;
			})
			.catch((error) =>
			{
				logger.error('"room.dump" request failed: %s', error);

				throw error;
			});
	}

	/**
	 * Get room's capabilities per kind.
	 *
	 * @return {RtpCapabilities}
	 */
	getCapabilities(kind)
	{
		logger.debug('getCapabilities() [kind:%s]', kind);

		// Ensure `kind` is 'audio' / 'video' / 'depth'.
		if (KINDS.indexOf(kind) === -1)
			throw new TypeError(`unsupported kind: ${kind}`);

		return this._capabilities[kind];
	}

	/**
	 * Create a Peer instance.
	 *
	 * @param {String} peerName - Peer identificator.
	 *
	 * @return {Peer}
	 */
	Peer(peerName)
	{
		logger.debug('Peer() [peerName:"%s]', peerName);

		if (this._closed)
			throw new errors.InvalidStateError('Room closed');

		if (!peerName || typeof peerName !== 'string')
			throw new TypeError('peerName must be a string');

		if (this._peers.has(peerName))
			throw new Error(`peer already exists [peerName:"${peerName}"]`);

		let peerId = utils.randomNumber();
		let internal =
		{
			roomId   : this._internal.roomId,
			peerId   : peerId,
			peerName : peerName
		};
		let sandbox =
		{
			getRtpReceiverById : (rtpReceiverId) =>
			{
				return this._rtpReceivers.get(rtpReceiverId);
			}
		};

		// Create a Peer instance.
		let peer = new Peer(internal, this._channel, sandbox);

		// Store the Peer instance and remove it when closed.
		this._peers.set(peerName, peer);
		peer.on('close', () =>
		{
			this._peers.delete(peerName);
		});

		// Listen for new RtpReceivers so we can associate new RtpSenders.
		peer.on('newrtpreceiver', (rtpReceiver) =>
		{
			// Store the RtpReceiver instance and remove it when closed.
			this._rtpReceivers.set(rtpReceiver.id, rtpReceiver);
			rtpReceiver.on('close', () => this._rtpReceivers.delete(rtpReceiver.id));
		});

		this._channel.request('room.createPeer', internal)
			.then(() =>
			{
				logger.debug('"room.createPeer" request succeeded');

				this.emit('newpeer', peer);
			})
			.catch((error) =>
			{
				logger.error('"room.createPeer" request failed: %s', error);

				peer.close(error, true);
			});

		return peer;
	}

	/**
	 * Get Peer.
	 *
	 * @param {String} peerName
	 *
	 * @return {Peer}
	 */
	getPeer(peerName)
	{
		return this._peers.get(peerName);
	}

	_setCapabilities(capabilities)
	{
		for (let kind of KINDS)
		{
			this._capabilities[kind] =
			{
				codecs           : [],
				headerExtensions : [],
				fecMechanisms    : []
			};

			let kindCapabilities = this._capabilities[kind];

			for (let codec of capabilities.codecs)
			{
				if (codec.kind === kind)
				{
					kindCapabilities.codecs.push(codec);
				}
				else if (codec.kind === '')
				{
					let clonedCodec = utils.clone(codec);

					clonedCodec.kind = kind;
					kindCapabilities.codecs.push(clonedCodec);
				}
			}

			// Ignore if there are no media codecs of this kind.
			if (kindCapabilities.codecs.length > 0)
			{
				for (let headerExtension of capabilities.headerExtensions)
				{
					if (headerExtension.kind === kind)
					{
						kindCapabilities.headerExtensions.push(headerExtension);
					}
					else if (headerExtension.kind === '')
					{
						let clonedHeaderExtension = utils.clone(headerExtension);

						clonedHeaderExtension.kind = kind;
						kindCapabilities.headerExtensions.push(clonedHeaderExtension);
					}
				}

				kindCapabilities.fecMechanisms = capabilities.fecMechanisms;
			}
		}
	}
}

module.exports = Room;
