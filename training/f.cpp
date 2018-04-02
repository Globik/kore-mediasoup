#include "deplibuv.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
//g++  -o main main.cpp
// g++ -o main.cpp deplibuv.o `pkg-config --cflags --libs libuv`
static void init();
static void destroy();
static void exits();
static void exite();
int main(){
	std::cout << "hallo\n";
	deplibuv::classinit();
	try{
	init();
	deplibuv::runloop();
	destroy();
	exits();
	}catch(std::exception& e){
	std::cout << e.what();
	std::abort();
	}
}
void init(){
deplibuv::printversion();
}
void destroy(){
deplibuv::classdestroy();
}
void exits(){
usleep(100000);
	std::_Exit(EXIT_SUCCESS);
}
void exite(){
usleep(10000);
std::_Exit(EXIT_FAILURE);
}