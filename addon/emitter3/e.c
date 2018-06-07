//github.com/benfleis/samples.git
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uv.h>
static uv_poll_t stdin_watcher;
static uv_poll_t stdout_watcher;
static char log_buf[4096];
static size_t log_buf_pos=0;
void log_buf_nul_term () { 
do{if(log_buf_pos < sizeof(log_buf)){ 
	printf("lbp < sizoof(log_buf).\n");
	log_buf[log_buf_pos]=0;
}else{printf("no < sizeof(log_buf).\n");}
  } while(0); 
}

static void stdout_cb(uv_poll_t*watcher,int status,int wevents){
int rv;
	//wevents=2,status=0
	rv=write(STDOUT_FILENO,log_buf,log_buf_pos);
	if(rv==log_buf_pos){
	printf("whole buf written. : %d %d wevents: %d , status: %d\n",rv, log_buf_pos,wevents,status);
	uv_poll_stop(&stdout_watcher);
	log_buf_pos=0;
	}else if(rv>=0){
	printf("memmove: %d = %d \n",rv,log_buf_pos);
	memmove(log_buf,log_buf+rv,log_buf_pos-rv);
	log_buf_pos-=rv;
	}else{
	fprintf(stderr,"write() returned error: %s",strerror(errno));
		exit(1);
	}
	log_buf_nul_term();
}
static void _log(const char*fmt,...){
va_list ap;
	va_start(ap,fmt);
	log_buf_pos+=vsnprintf(log_buf+log_buf_pos,sizeof(log_buf)-log_buf_pos,fmt,ap);
	va_end(ap);
	log_buf_nul_term();
	uv_poll_start(&stdout_watcher,UV_WRITABLE,stdout_cb);
}
static void stdin_cb(uv_poll_t*watcher,int status,int revents){
	printf("in\n");
char buf[4096];
	int rv;
	//revents=1, status=0
	rv=read(STDIN_FILENO,buf,sizeof(buf));
	if(rv>0){
	_log("read()'d %d bytes. revents: %d, status: %d\n",rv,revents,status);
		if(rv==0){
		_log("exiting on end of stream.\n");
			uv_poll_stop(&stdin_watcher);
		}
	}else if(errno !=EAGAIN && errno !=EINPROGRESS){
	fprintf(stderr,"read() returned error: %s",strerror(errno));
	}
}
static int set_non_blocking(int fd){
int val=fcntl(fd,F_GETFL,0);
	return val==-1 ? -1 : fcntl(fd,F_SETFL,val | O_NONBLOCK);
}
int main(int argc,const char* const*argv){
printf("gimme your inputs\n");
	set_non_blocking(STDIN_FILENO);
	set_non_blocking(STDOUT_FILENO);
	uv_loop_t*loop=uv_default_loop();
	uv_poll_init(loop,&stdin_watcher,STDIN_FILENO);
	uv_poll_init(loop,&stdout_watcher,STDOUT_FILENO);
	uv_poll_start(&stdin_watcher,UV_READABLE,stdin_cb);
	uv_run(loop,0);
	return 0;
}


























