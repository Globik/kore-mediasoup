INC = -I /usr/local/include/lwan
LIB = -L /usr/local/lib
DOP = -llwan -lpthread -lz -L/usr/lib -llua5.1 -lm
a: coro.c
	gcc $(INC) -o c coro.c $(LIB) -llwan -lpthread -lz -L/usr/lib -llua5.1 -lm
b: coro2.c
	gcc $(INC) -o c2 coro2.c $(LIB) $(DOP)
c: coro3.c
	gcc $(INC) -o c3 coro3.c $(LIB) $(DOP) `pkg-config --cflags --libs libuv`