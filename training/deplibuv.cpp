#include "deplibuv.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
extern void*pt2obj;
//extern uv_callback_t cb_sum2;
// g++ -std=c++11 `pkg-config --cflags libuv` -c deplibuv.cpp 

// gcc `pkg-config --cflags libuv` -c uv_callback.c 
uv_loop_t* deplibuv::loop{nullptr};
//extern uv_callback_t cb_sum2;
uv_callback_t cb_sum2;

void deplibuv::classinit(){
	std::cout << "here class init\n";
int err;
	deplibuv::loop=new uv_loop_t;
	err=uv_loop_init(deplibuv::loop);
	if(err !=0){
	std::cout << "libuv init failed\n";
	std::abort();
	}
	//int rc=uv_callback_init(deplibuv::loop,&cb_sum2, deplibuv::on_sum2, UV_DEFAULT);
	//std::cout << "in deplibuv.cpp rc2: " << rc << std::endl;
}
void deplibuv::display(char*text){std::cout << text << std::endl;};
void deplibuv::wrapper_to_call_display(char*string){
deplibuv* myself=(deplibuv*)pt2obj;
myself->display(string);
}
int deplibuv::hello(const std::string& s)
	{
	std::cout << "hello " << s << '\n';
		sleep(3);
		return 1;
	int rc=uv_callback_fire(&cb_sum2,(void*)"suka",NULL);
	std::printf("rcoooooo1: %d\n",rc);
		rc=uv_callback_fire(&cb_sum2,(void*)"fucker",NULL);
	std::printf("rcoooooo2: %d\n",rc);
		rc=uv_callback_fire(&cb_sum2,(void*)"putin",NULL);
	std::printf("rcoooooo3: %d\n",rc);
		rc=uv_callback_fire(&cb_sum2,(void*)"gebbels",NULL);
	std::printf("rcoooooo4: %d\n",rc);
		rc=uv_callback_fire(&cb_sum2,(void*)"hitler",NULL);
	std::printf("rcoooooo5: %d\n",rc);
		rc=uv_callback_fire(&cb_sum2,(void*)"error",NULL);
	std::printf("rcoooooo6: %d\n",rc);
		return 0;
	}
void deplibuv::classdestroy(){
if(deplibuv::loop==nullptr){ 
std::cout << "loop was not allocated.\n";
std::abort();
}
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
	
	int rc=uv_callback_init(deplibuv::getloop(),&cb_sum2, on_sum2, UV_DEFAULT);
	std::cout << "in deplibuv.cpp rc2: " << rc << std::endl;
	//rc=uv_callback_fire(&cb_sum2,(void*)"suka",NULL);
	//std::printf("rc: %d\n",rc);
	
	
	std::cout << "Loop was allocated?" << std::endl;
	uv_run(deplibuv::loop,UV_RUN_DEFAULT);
}