#plugin
INCLS = -I. `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs glib-2.0`
OBS = plugin.o echo.o helper.o
CFLAGS=-g
a: plugin.c
	gcc $(INCLS) -c plugin.c
b: echo.c
	gcc $(INCLS) -c echo.c
h: helper.c
	gcc $(INCLS) -c helper.c
q: q.c
	gcc $(INCLS) -o q q.c $(OBS) $(LIBS)

j: echo.c
	gcc $(INCLS) $(CFLAGS) -c -fpic echo.c 
	
v: v
	gcc -shared -o libecho.so echo.o `pkg-config --libs glib-2.0` -pthread -ldl
