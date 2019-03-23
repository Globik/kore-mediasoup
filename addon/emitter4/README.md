## SOCK_SEQPACKET client(node.js addon)

Trying to implement the sock_seqpacket(client) based on [uv_poll_t](http://docs.libuv.org/en/v1.x/poll.html) routine. (Done)

Using [The Janus WebRTC gateway's](https://github.com/meetecho/janus-gateway)
[janus-pfunix transport](https://github.com/meetecho/janus-gateway/blob/master/transports/janus_pfunix.c) as a SOCK_SEQPACKET server.

1. Run janus
2. Run node app1.js

[m.c](https://github.com/Globik/kore-mediasoup/blob/master/addon/emitter4/m.c) -
is the implementation of SOCK_SEQPACKET client in node.js [addon N-API](https://nodejs.org/dist/latest-v9.x/docs/api/n-api.html).
The N-API is a C API that ensures ABI stability across Node.js versions and different compiler levels.

#  Videobroadcast as webinar

Client [videoBroadcast.html](https://github.com/Globik/kore-mediasoup/blob/master/addon/emitter4/public/html/videoBroadcast.html)

server [app.js](https://github.com/Globik/kore-mediasoup/blob/master/addon/emitter4/app.js)

### Publisher

1. Send Offer to Janus
2. Get Answer from Janus

### Subscriber

1. Get Offer from Janus
2. Send Answer to Janus
