a: libuv.cpp
	g++ -std=c++11 -fpic -c libuv.cpp
b: b
	g++ -shared  -o libfuk.so libuv.o `pkg-config --libs libuv`	
c: s.c
	gcc -o s s.c -Wl,-rpath /home/globik/kore-mediasoup/training/luvi -L/home/globik/kore-mediasoup/training/luvi -lfuk