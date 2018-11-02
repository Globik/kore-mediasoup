# kore-mediasoup
It's time to hack [mediasoup](https://github.com/versatica/mediasoup) - Cutting Edge WebRTC Videoconferencing written in C++.

Based on [Version 1.2.8](https://github.com/versatica/mediasoup/tree/1.2.8)

# The goal

I just want to get it work from within a [kore](https://github.com/jorisvink/kore)  web framework(written in C) in a dedicated thread.

Just like here [https://github.com/Globik/kore.io_websocket/tree/master/mediasoup_1](https://github.com/Globik/kore.io_websocket/tree/master/mediasoup_1)

As such I wanna port the mediasoup's [javascript API](https://github.com/versatica/mediasoup/tree/1.2.8/lib) to the C part.

## Work in progress:

It's here:

[mediasoup\_1](https://github.com/Globik/kore.io_websocket/tree/master/mediasoup_1). As an example and proof of concept.

So far so good, I have replaced the UnixStreamSocket interface with the [uv\_callback](https://github.com/litesync/uv_callback) interface.

In plan, to use the kore's build-in socket for some binary streams from the mediasoup's worker.

## Janus WebRTC gateway communicates with nodejs via SOCK_SEQPACKET written in C addon N-API

It's here:
[https://github.com/Globik/kore-mediasoup/tree/master/addon/emitter4](https://github.com/Globik/kore-mediasoup/tree/master/addon/emitter4)

Based on uv_poll_t routine.
