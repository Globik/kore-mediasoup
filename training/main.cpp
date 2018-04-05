#include "deplibuv.hpp"
#include "uv_callback.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <memory.h>
#include <string>
//g++  -o main main.cpp
// g++ -std=c++11 -c deplibuv.cpp `pkg-config --cflags libuv`
// g++ -std=c++11 -o m main.cpp deplibuv.o `pkg-config --cflags --libs libuv`
static void init();
static void destroy();
static void exits();
static void exite();
void*pt2obj;
uv_callback_t suka,result,stop_worker;
//uv_callback_t cb_sum2;
typedef std::function<int (const std::string&)> examplefunc;
struct numbers{
	int a;
};
void * on_progress(uv_callback_t*,void*);
void * on_result(uv_callback_t*,void*);
void * stop_worker_cb(uv_callback_t*,void*);
void * on_sum2(uv_callback_t *callback,void*data){
	std::printf("ROCK-N-ROLL?? %s\n", (char*)data);
	return data;
	}
void doit(void(*pfunc)(char*text)){
pfunc("text");
}

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
	struct numbers*req;
//typedef std::function<void (const std::string&)> examplefunc;
//typedef std::function<void(const std::string&)> examplefunc;
deplibuv ob;
//pt2obj=(void*)&ob;
//doit(deplibuv::wrapper_to_call_display);
	
//std::string str((char*)value);
examplefunc f=std::bind(&deplibuv::hello,&ob,std::placeholders::_1);
//instance.hello(str)
int mu=f((char*)value);
	std::printf("int %d\n",mu);
	if(mu)return (void*)mu;
	
	/*
	int rc=uv_callback_init(deplibuv::getloop(),&cb_sum2, deplibuv::on_sum2, UV_DEFAULT);
	std::cout << "in deplibuv.cpp rc2: " << rc << std::endl;
	rc=uv_callback_fire(&cb_sum2,(void*)"suka",NULL);
	std::printf("rc: %d\n",rc);
	*/
	
return value;
}
void * on_result(uv_callback_t*handle,void*value){
//std::printf("ON result occured: %s.\n",(char*)value);
//	*((double*)
	std::printf("on result occured: %d\n",(int)value);
uv_callback_fire(&stop_worker,NULL,NULL);
return NULL;
}
void * stop_worker_cb(uv_callback_t*handle,void*arg){
std::printf("on stop worker cb\n");
uv_stop(((uv_handle_t*)handle)->loop);
return NULL;
}