#include "deplibuv.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

uv_loop_t* deplibuv::loop{nullptr};


void deplibuv::classinit(){
	std::cout << "here class init\n";
int err;
	deplibuv::loop=new uv_loop_t;
	err=uv_loop_init(deplibuv::loop);
	if(err !=0){
	std::cout << "libuv init failed\n";
	std::abort();
	}
	
}
void deplibuv::display(char*text){std::cout << text << std::endl;};


void deplibuv::classdestroy(){
if(deplibuv::loop==nullptr){ 
std::cout << "loop was not allocated.\n";
std::abort();
}
//uv_stop(deplibuv::loop);
//	usleep(100000);
uv_loop_close(deplibuv::loop);
delete deplibuv::loop;
std::cout<<"Loop was destroyd?"<<std::endl;
}
void deplibuv::printversion(){
//std::printf("version %s\n", uv_version_string());
	std::cout << "version:  " << uv_version_string() << std::endl;
}
void deplibuv::runloop(){
if(deplibuv::loop==nullptr){
std::cout << "loop was not allocated 2.\n"<< std::endl;
std::abort();
}
	
	
	std::cout << "Loop was allocated?" << std::endl;
	uv_run(deplibuv::loop,UV_RUN_DEFAULT);
}