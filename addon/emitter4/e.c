#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>


#include <uv.h>
#define socket_name "/home/globik/fuck"
static uv_poll_t stdin_watcher;
static uv_poll_t stdout_watcher;
static uv_os_sock_t data_socket;
static char log_buf[4096];
static size_t log_buf_pos=0;
static void stdout_cb(uv_poll_t*watcher,int status,int wevents){
	/*
int rv;
	//wevents=2,status=0
	rv=write(data_socket,log_buf,log_buf_pos);
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
	*/
}
int suka=0;
static void stdin_cb(uv_poll_t*watcher,int status,int revents){
	suka++;
	if(suka==10){
	uv_poll_stop(&stdin_watcher);
	close(data_socket);
	}
	printf("REVENTS: %d STATUS: %d\n",revents,status);
//char buf[4096];
	int rv;
	//revents=1, status=0
	if(revents==2){
	rv=write(data_socket,"mama\0",5);
	printf("rv write: %d\n",rv);
	}else if(revents==3){
		int ret;
	ret=read(data_socket,log_buf,4096);
if(ret==-1){exit(1);}
		printf("REad: %d\n",ret);
		log_buf[ret-1]=0;
		printf("read: %s\n",log_buf);
		
	}else{
	printf("revents default: %d",revents);
	}
	/*
	rv=read(data_socket,buf,sizeof(buf));
	if(rv>0){
		printf("rv: %d revents: %d status: %d\n",rv,revents,status);
	//_log("read()'d %d bytes. revents: %d, status: %d\n",rv,revents,status);
		if(rv==0){
			printf("exiting?\n");
		//_log("exiting on end of stream.\n");
			uv_poll_stop(&stdin_watcher);
		}
	}else if(errno !=EAGAIN && errno !=EINPROGRESS){
	fprintf(stderr,"read() returned error: %s",strerror(errno));
	}
	*/
}
int main(){
	int ret;
	struct sockaddr_un addr;
	data_socket=socket(AF_UNIX,SOCK_SEQPACKET | O_NONBLOCK,0);
	if(data_socket==-1){
	printf("data_socket err: %d\n",data_socket);
	perror("socket");
	exit(EXIT_FAILURE);
	}
	memset(&addr,0,sizeof(struct sockaddr_un));
	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path,socket_name,sizeof(addr.sun_path)-1);
	ret=connect(data_socket,(const struct sockaddr*)&addr,sizeof(struct sockaddr_un));
if(ret==-1){
fprintf(stderr,"the server is down.\n");
	close(data_socket);
	exit(EXIT_FAILURE);
}
	uv_loop_t*loop=uv_default_loop();
	uv_poll_init(loop,&stdin_watcher, data_socket);
	//uv_poll_init(loop,&stdout_watcher, STDOUT_FILENO);
	uv_poll_start(&stdin_watcher, UV_READABLE | UV_WRITABLE,stdin_cb);
	uv_run(loop,0);
return 0;
}