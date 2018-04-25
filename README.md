# kore-mediasoup
It's time to hack [mediasoup](https://github.com/versatica/mediasoup) - Cutting Edge WebRTC Videoconferencing written in C++
Based on mdiasoup [Version 1.2.8](https://github.com/versatica/mediasoup/tree/1.2.8)

# The goal

I just want to get it work from within [kore](https://github.com/jorisvink/kore)  a web framework(written in C) in a kore's dedicated thread.

Wanna port the mediasoup's [javascript API](https://github.com/versatica/mediasoup/tree/1.2.8/lib) to the C part.

## Work in progress:

It's here:

[mediasoup\_1](https://github.com/Globik/kore.io_websocket/tree/master/mediasoup_1). As an example and proof of concept.

So far so good, I have replaced the UnixStreamSocket interface with the [uv\_callback](https://github.com/litesync/uv_callback) interface.

In plan, for the binary streaming from the mediasoup lib stuff to use the build-in kore's socket.