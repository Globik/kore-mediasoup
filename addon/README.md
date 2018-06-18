### Some folders and directories 

emitter4 - an experiment with uv_poll_t for a socket type SOCK_SEQPACKET - a client. This is nodejs addon in C N-API.
As a server SOCK_SEQPACKET I'm using JANUS WebRTC gateway with his pfunix transport. The WebRTC DataChannel API works kike expected.
Based on janus.plugin.echotest

emitter5 - a little experiment with Node.js addon C N-API and dedicated thread for glib loop ecosystem. It works!