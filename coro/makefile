#/home/globik/awaituv/inc/awaituv.h
#-std=gnu++11 -std=c++11 fcoroutines-ts

# /home/globik/q/libs/q/include/q/promise.hppxxx
# /home/globik/q/build/lib/libq.a
INC= -I /home/globik/awaituv/inc
Q_INC = -I /home/globik/q/libs/q/include
Q_LIB = -L /home/globik/q/build/lib -lq
a: a.cpp
	g++  -std=c++11 $(INC) -o a a.cpp -luv -lpthread -lstdc++
test: test.cpp
	g++ -std=c++11 -o test test.cpp -lstdc++
pr: pr.cpp
	g++ -std=gnu++11 $(Q_INC) -o pr pr.cpp $(Q_LIB) -pthread
probe2: probe2.cpp
	g++ -std=gnu++11 -o probe2 probe2.cpp -pthread
