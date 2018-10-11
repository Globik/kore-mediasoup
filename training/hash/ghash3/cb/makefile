INC= -I.
EMIT = -I /home/globik/ee.c/src
LISTI = -I /home/globik/ee.c/deps/list
mediasoup: mediasoup.c
	gcc $(INC) $(EMIT) $(LISTI) -c mediasoup.c
channel: channel.c
	gcc $(INC) $(EMIT) $(LISTI) -c channel.c
main: main.c
	gcc $(INC) $(EMIT) $(LISTI) -o main main.c channel.o mediasoup.o -lee
