#include <uv.h>
#include <stdio.h>
#include "lwan-coro.h"
uv_loop_t*loop;
uv_fs_t open_req;
int bresult=-1;
int fucker=1;
typedef void (*vop)(uv_fs_t*);
struct file{
uv_loop_t*loop;
const char*path;
vop on_vop;
int res;
};
//void open_cb(uv_fs_t*req);
char buf[1024];
const char*path="binding.gyp";

static int producer(struct coro*coro,void*data){
	//void open_cb(uv_fs_t*);
struct file*f=(struct file*)data;
	int r=-1;
	//while(r==bresult){ 
	//coro_yield(coro,1);
	open_req.data=f;
	
	
	void open_cb(uv_fs_t*req){
	printf("open cb???\n");
	struct file*f=(struct file*)req->data;
int result=req->result;
	if(result<0){
	fprintf(stderr,"error at opening file: %s\n",uv_strerror(result));
	}
	printf("result: %d\n",result);
	f->res=result;
	fucker=1;
	printf("f res %d\n",f->res);
		
	//coro_resume(coro);
	//uv_fs_req_cleanup(req);
	coro_yield(coro,1);
	__builtin_unreachable();
}
	
	r=uv_fs_open(f->loop,&open_req,f->path,O_RDONLY,S_IRUSR,open_cb);
	if(r){
	fprintf(stderr,"error opening file: %s\n",uv_strerror(r));
		f->res=22;
	//coro_yield(coro,2);
		coro_yield(coro,0);
	__builtin_unreachable();
	}
	//f->res=44;
	
	printf("ffff: %d\n",f->res);
	//coro_yield(coro,1);
	//__builtin_unreachable();
	
	return 0;
}



int main(){
	loop=uv_default_loop();
	struct coro_switcher switcher;
	struct file f={.loop=loop,.path=path,.on_vop=NULL,.res=0};
	struct coro*coro=NULL;

	/*
	int r=uv_fs_open(loop,&open_req,path,O_RDONLY,S_IRUSR,open_cb);
	if(r){
	fprintf(stderr,"error opening file: %s\n",uv_strerror(r));
	}
	
	printf("r: %d\n",r);
	*/
	coro=coro_new(&switcher,producer,&f);
	while(coro_resume(coro)) {
	//coro_resume(coro);
	printf("bresult %d\n",f.res);
	}
	
	uv_run(loop,UV_RUN_DEFAULT);
	coro_free(coro);
	coro=NULL;
	return 0;
}
/*
void open_cb(uv_fs_t*req){
	printf("open cb???\n");
	struct file*f=(struct file*)req->data;
int result=req->result;
	if(result<0){
	fprintf(stderr,"error at opening file: %s\n",uv_strerror(result));
	}
	printf("result: %d\n",result);
	f->res=result;
	fucker=1;
	printf("f res %d\n",f->res);
	//coro_resume(coro);
	uv_fs_req_cleanup(req);
	
	//__builtin_unreachable();
}*/
