a: deplibuv.cpp
	g++ -std=c++11 `pkg-config --cflags libuv` -c deplibuv.cpp
b: main.cpp
	g++ -std=c++11 -o m main.cpp deplibuv.o uv_callback.o `pkg-config --cflags --libs libuv`