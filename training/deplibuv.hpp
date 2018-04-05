#ifndef LIBUV_HPP
#define LIBUV_HPP
#include <uv.h>
#include "uv_callback.h"
#include <iostream>
#include <functional>
#include <string>
//void*pt2obj;
void * on_sum2(uv_callback_t *callback,void*data);
extern uv_callback_t cb_sum2;
class deplibuv
{
public:
	static void classinit();
	static void classdestroy();
	static void printversion();
	static void runloop();
	static uv_loop_t* getloop();
	static uint64_t gettime();
	
	int hello(const std::string& s);
	/*{
	std::cout << "hello " << s << '\n';
	}
	*/
	/*
	static void * on_sum2(uv_callback_t *callback,void*data){
		std::printf("ODER?? %s\n", (char*)data);
	//int a=9;
	
	return data;
	}
	*/
	
	void display(char*text);//{std::cout << text << std::endl;};
	static void wrapper_to_call_display(char*text);
private:
	static uv_loop_t*loop;
};
inline uv_loop_t* deplibuv::getloop(){
return deplibuv::loop;
}
inline uint64_t deplibuv::gettime(){
return uv_now(deplibuv::loop);
}
#endif