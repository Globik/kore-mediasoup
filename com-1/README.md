# As cpp main executable

Successfully compiled mediasoup executable at maximum level.
Replaced UnixStreamSocket with an uv_callback.c interface as a communication channel between mediasoup server and C++ mama.cpp executable.
Yeah, I got it.

# TODO:
- to mimic the mediasoup client, aka mediasoup.js? 

## I don't like that:

There are a lot of new Set() and new Map() for all kinds of javascript classes in the mediasoup.js's kitchen,
but are they really any need, I mean all that stuff with duplication(triplication!!!)?
Also in node.js app there are as a minimum - the new Map() for the rooms and the new Map() for the peerConnections. 
Plus the websocket's inner Memory for the new connections also takes a lot of place.
It could be fine directly to store all those rooms and peers on the mediasoup client level and on the app level at a time.
Even it could be nice to use a database for those purposes. 
Yup, it can cause some perfomance issues but for it will be much more place for memory in the app itself.

Implement the sdp transformer lib written on C++.