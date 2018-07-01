///home/globik/awaituv/inc/awaituv.h
#include <uv.h>
#include <awaituv.h>
future_t<void> start(){
for(int i=0;i<10;++){
string_buf_t buf("kkk\n");
	fs_t req;
	(void) co_await fs_write(uv_default_loop(),&req,1,&buf,1,-1);
}
}
int main(){
return 0;
}