## SOCK_SEQPACKET client(node.js addon)

Trying to implement the sock_seqpacket(client) based on [uv_poll_t](http://docs.libuv.org/en/v1.x/poll.html) routine. (Done)

Using [The Janus WebRTC gateway's](https://github.com/meetecho/janus-gateway)
[janus-pfunix transport](https://github.com/meetecho/janus-gateway/blob/master/transports/janus_pfunix.c) as a SOCK_SEQPACKET server.

1. Run janus
2. Run node app1.js

[m.c](https://github.com/Globik/kore-mediasoup/blob/master/addon/emitter4/m.c) -
is the implementation of SOCK_SEQPACKET client in node.js [addon N-API](https://nodejs.org/dist/latest-v9.x/docs/api/n-api.html).
The N-API is a C API that ensures ABI stability across Node.js versions and different compiler levels.

# Working DRAFTS(RECOMMENDATIONS)

## Janus WebRTC gateway hacking in nodejs environment based on pfunix transport

1. As such [https://github.com/meetecho/janus-gateway/blob/b9c3d7471a28795c5d1e397eaabeac724c1f69f2/transports/janus_pfunix.c#L447](https://github.com/meetecho/janus-gateway/blob/b9c3d7471a28795c5d1e397eaabeac724c1f69f2/transports/janus_pfunix.c#L447)
should be modified. The connection to client should NOT be closed in case of session timeout.
The client should self to decide when to close and when to connect to Janus

2. Janus's notifications folders in JASON object should be explicitly defined.
NOT "success" but "success_create", "success_attach", "success_detach" etc.
NOT "ack" but "pong_ack" etc

3. On nodejs part one should to add additional folder "type" with value "janus"

The session, plugin attach should be created at nodejs runtime and then broadcasting to clients. 

This work is one of prototypes to fututure CMS in node.js in javascript and kore-webframwork in C.
Use case - a website for live videostreaming(around o-clock) from IP-cameras. Maximum 6 cameras. 500 users at a time.
Payment for video show will be expected in bitcoins.