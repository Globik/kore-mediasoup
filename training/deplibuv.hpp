#ifndef LIBUV_HPP
#define LIBUV_HPP
#include <uv.h>
class deplibuv
{
public:
	static void classinit();
	static void classdestroy();
	static void printversion();
	static void runloop();
	static uv_loop_t* getloop();
	static uint64_t gettime();
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