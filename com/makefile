INC = -I ./channel -I .
INC_CPPJSON=-I /home/globik/.local/share/Trash/files/deps.2/jsoncpp/jsoncpp/include
# /home/globik/kore.io_websocket/uv3/libuv_callback.so
CBINC = -I /home/globik/kore.io_websocket/uv3
I=$(INC) $(INC_CPPJSON) $(CBINC) `pkg-config --cflags libuv`
CBLIB = -Wl,-rpath /home/globik/kore.io_websocket/uv3 -L /home/globik/kore.io_websocket/uv3 -luv_callback
LIBJSON = -L /home/globik/alikon/node_modules/mediasoup/worker/out/Release -ljsoncpp $(CBLIB)

LSOUP = -Wl,-rpath /home/globik/kore-mediasoup/com -L /home/globik/kore-mediasoup/com -lsoup

SRC = deplibuv.cpp Loop.cpp Room.cpp  UnixStreamSocket.cpp Notifier.cpp Request.cpp Logger.cpp SignalsHandler.cpp

#handle_UnixStreamSocket.o
OB = deplibuv.o Loop.o Room.o  UnixStreamSocket.o Notifier.o Request.o Logger.o SignalsHandler.o

L = `pkg-config --libs libuv` $(LIBJSON)

LC = `pkg-config --libs libuv` $(CBLIB)

a: Notifier.cpp
	g++ -std=c++11 $(I) -c Notifier.cpp
b: Request.cpp
	g++ -std=c++11 $(I) -c Request.cpp
c: Room.cpp
	g++ -std=c++11 $(I) -c Room.cpp
d: Loop.cpp
	g++ -fpic -std=c++11 $(I) -c Loop.cpp
e: SignalsHandler.cpp
	g++ -std=c++11 $(I) -c SignalsHandler.cpp
f: deplibuv.cpp
	g++ -std=c++11 $(I) -c deplibuv.cpp
g: UnixStreamSocket.cpp
	g++ -fpic -std=c++11 $(I) -c UnixStreamSocket.cpp
h: handle_UnixStreamSocket.cpp
	g++ -std=c++11 $(I) -c handle_UnixStreamSocket.cpp
i: Logger.cpp
	g++ -std=c++11 $(I) -c Logger.cpp
k: main.cpp
	g++ -std=c++11 $(I) -o main main.cpp $(OB) $(L)
l: l
	g++ -fpic -std=c++11 $(I) -c $(SRC)
me: me
	g++ -shared -o libsoup.so $(OB) $(LIBJSON)
n: m.c
	gcc $(INC) $(CBINC) -o m m.c $(LC) $(LSOUP)