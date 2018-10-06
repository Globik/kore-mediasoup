# training/hash/ghash3
INC = `pkg-config --cflags glib-2.0` -I /home/globik/ee.c/deps/list
LINKID = -I /usr/src/linux-headers-3.2.0-23/include
EMIT = -I /home/globik/ee.c/src
LISTI = -I /home/globik/ee.c/deps/list
a: m.c
	gcc $(INC) -o m m.c `pkg-config --libs glib-2.0`
d: d.c
	gcc $(INC) -o d d.c -lee `pkg-config --libs glib-2.0`
dig: dig.c
	gcc -o dig dig.c
e: e.c
	gcc $(EMIT) $(LISTI) -o e e.c -lee
ec: ec.c
	gcc $(EMIT) $(LISTI) -o ec ec.c -lee
ec2: ec2.c
	gcc $(EMIT) $(LISTI) -o ec2 ec2.c -lee `pkg-config --libs lwan`
