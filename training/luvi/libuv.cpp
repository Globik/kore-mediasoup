#include "libuv.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

uv_loop_t* deplibuv::loop{nullptr};

//uv_callback_t cb_sum2;

void deplibuv::classinit(){
	std::cout << "here class init\n";
int err;
	deplibuv::loop=new uv_loop_t;
	err=uv_loop_init(deplibuv::loop);
	if(err !=0){
	std::cout << "libuv init failed\n";
	exit(1);
	}
	//int rc=uv_callback_init(deplibuv::loop,&cb_sum2, deplibuv::on_sum2, UV_DEFAULT);
	//std::cout << "in deplibuv.cpp rc2: " << rc << std::endl;
}


void deplibuv::classdestroy(){
if(deplibuv::loop==nullptr){ 
std::cout << "loop was not allocated.\n";
//std::abort();
exit(1);	
}
uv_loop_close(deplibuv::loop);
delete deplibuv::loop;
std::cout<<"Loop was destroyd?"<<std::endl;
}
void ini(){
deplibuv::classinit();
}
void printi(){
deplibuv::printversion();
}
void runi(){
deplibuv::runloop();
}
void destri(){
deplibuv::classdestroy();
}
void deplibuv::printversion(){
//std::printf("version %s\n", uv_version_string());
	std::cout << "version:  " << uv_version_string() << std::endl;
}
void deplibuv::runloop(){
if(deplibuv::loop==nullptr){
std::cout << "loop was not allocated 2.\n"<< std::endl;
exit(1);
}
	/*
	int rc=uv_callback_init(deplibuv::getloop(),&cb_sum2, on_sum2, UV_DEFAULT);
	std::cout << "in deplibuv.cpp rc2: " << rc << std::endl;
	//rc=uv_callback_fire(&cb_sum2,(void*)"suka",NULL);
	//std::printf("rc: %d\n",rc);
	*/
	
	std::cout << "Loop was allocated?" << std::endl;
	uv_run(deplibuv::loop,UV_RUN_DEFAULT);
}