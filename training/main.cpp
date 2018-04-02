#include "deplibuv.hpp"
#include "uv_callback.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <memory.h>
//g++  -o main main.cpp
// g++ -std=c++11 -c deplibuv.cpp `pkg-config --cflags libuv`
// g++ -std=c++11 -o m main.cpp deplibuv.o `pkg-config --cflags --libs libuv`
static void init();
static void destroy();
static void exits();
static void exite();

uv_callback_t suka,result,stop_worker;

void * on_progress(uv_callback_t*,void*);
void * on_result(uv_callback_t*,void*);
void * stop_worker_cb(uv_callback_t*,void*);

int main(){
	std::cout << "hallo\n";
	deplibuv::classinit();
	try{
	init();
	uv_callback_init(deplibuv::getloop(),&suka,on_progress,UV_DEFAULT);	
    uv_callback_fire(&suka,(void*)"MAMA", &result);
	uv_callback_init(deplibuv::getloop(),&result,on_result,UV_DEFAULT);
	uv_callback_init(deplibuv::getloop(),&stop_worker,stop_worker_cb,UV_COALESCE);
	// uv_callback_fire(&stop_worker,NULL,NULL);
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
std::cout<<"exit success?"<<std::endl;
usleep(100000);
std::_Exit(EXIT_SUCCESS);
}
void exite(){
std::cout<<"exit failure?"<<std::endl;
usleep(10000);
std::_Exit(EXIT_FAILURE);
}
void * on_progress(uv_callback_t*handle,void*value){
std::printf("progress: %s\n",(char*)value);
return value;
}
void * on_result(uv_callback_t*handle,void*value){
std::printf("ON result occured: %s.\n",(char*)value);
uv_callback_fire(&stop_worker,NULL,NULL);
return NULL;
}
void * stop_worker_cb(uv_callback_t*handle,void*arg){
std::printf("on stop worker cb\n");
uv_stop(((uv_handle_t*)handle)->loop);
return NULL;
}