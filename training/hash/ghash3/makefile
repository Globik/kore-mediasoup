# training/hash/ghash3
INC = `pkg-config --cflags glib-2.0` -I /home/globik/ee.c/deps/list
LINKID = -I /usr/src/linux-headers-3.2.0-23/include
a: m.c
	gcc $(INC) -o m m.c `pkg-config --libs glib-2.0`
d: d.c
	gcc $(INC) -o d d.c -lee `pkg-config --libs glib-2.0`
dig: dig.c
	gcc -o dig dig.c