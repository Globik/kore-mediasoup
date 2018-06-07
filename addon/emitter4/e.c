#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/eventfd.h>
#include <stdint.h>

#include <sys/un.h>
#include <sys/types.h>


#include <uv.h>
#define socket_name "/home/globik/fuck"
static uv_poll_t stdin_watcher;
static uv_poll_t sockin_watcher,sockout_watcher,disconnect_watcher;
static uv_os_sock_t data_socket;

int evfd;

uint64_t u;
//static char log_buf[4096];
//static size_t log_buf_pos=0;
static void on_eventfd_read(uv_poll_t*,int,int);
static void on_sock_read(uv_poll_t*,int,int);
static void on_sock_write(uv_poll_t*,int,int);
static void on_disconnect(uv_poll_t*watcher,int status,int revents);
static void on_clo(uv_handle_t*);

int duka=0;
static void on_sock_read(uv_poll_t*watcher,int status,int levents){
char buffer[512];
duka++;
if(duka==10){
uv_poll_stop(&sockout_watcher);
close(data_socket);
close(evfd);
	}
printf("ON_SOCK_READ: LEVENTS: %d STATUS: %d\n",levents,status);
	int ret;
if(levents & UV_READABLE){
	ret=read(data_socket,buffer,512);
if(ret==-1){
perror("read");
fprintf(stderr,"read error occured\n");
uv_poll_stop(&stdin_watcher);
uv_poll_stop(&sockin_watcher);
uv_poll_stop(&sockout_watcher);
close(data_socket);
close(evfd);
exit(1);
}
buffer[ret-1]=0;
fprintf(stderr,"result => %s\n",buffer);
//uv_poll_stop(&sockout_watcher);
//uv_poll_start(&stdin_watcher,UV_READABLE,stdin_cb);
	ssize_t slen;
	//slen=write(evfd,&u, sizeof(uint64_t));
	//if(slen !=sizeof(uint64_t)){printf("!slen\n");close(evfd);close(data_socket);exit(EXIT_FAILURE);}else{printf("slen is ok\n");}
}else if(levents & UV_DISCONNECT){
printf("disckonnect\n");
}else{
printf("UNKNOWN\n");
}
	uv_poll_stop(&sockout_watcher);

uv_close((uv_handle_t*)&stdin_watcher,on_clo);
uv_close((uv_handle_t*)&sockout_watcher, on_clo);
uv_close((uv_handle_t*)&sockin_watcher,on_clo);

}
int buka=0;

static void on_sock_write(uv_poll_t*watcher,int status,int mevents){
buka++;int ret;
	if(buka==10){
	uv_poll_stop(&sockin_watcher);
		close(data_socket);
		uv_poll_stop(&stdin_watcher);
		close(evfd);
	}
	
	printf("SOCK_CB: MEVENTS: %d STATUS: %d\n",mevents,status);
	if(mevents & UV_WRITABLE){
	printf("Uv writable\n");
char buf[512];

strcpy(buf,"Hallo world!");
		char*s=watcher->data;
		printf("SSSSSSSS: %s\n",s);
int leni=strlen(buf)+1;
ret=send(data_socket,buf, leni, 0);
if(ret==-1){
perror("write2");
close(data_socket);
exit(EXIT_FAILURE);
}
printf("leni: %d, ret: %d\n",leni,ret);
uv_poll_stop(&sockin_watcher);
	printf("POINT!\n");
uv_poll_start(&sockout_watcher, UV_READABLE | UV_DISCONNECT, on_sock_read);
	printf("POINT2\n");
}else if(mevents & UV_DISCONNECT){
	printf("DISCONNECT CAME\n");
	}else{
	printf("unknown\n");
	}

}
// 2 write
// 1 read
int suka=0;
static void on_eventfd_read(uv_poll_t*watcher,int status,int revents){
	suka++;
	printf("sucka: %d",suka);
	if(suka==10){
	uv_poll_stop(&stdin_watcher);
	close(evfd);
	}
	sockin_watcher.data="what the fuck?";
	printf("REVENTS: %d STATUS: %d\n",revents,status);
	ssize_t mu=read(evfd,&u,sizeof(uint64_t));
	if(mu !=sizeof(uint64_t)){printf("ev read not size64\n");}else{
	printf("return ev read %lld\n",u);
	uv_poll_start(&sockin_watcher, UV_WRITABLE | UV_DISCONNECT, on_sock_write);
	//uv_poll_start(&disconnect_watcher,UV_DISCONNECT,on_disconnect);
	}

}
void on_clo(uv_handle_t*h){
printf("on_clo occured.\n");
printf(" h: %p, h->data: %p\n",h,h->data);
if(h->data){
printf("some maining data: %s\n",(char*)h->data);
}
}
void on_disconnect(uv_poll_t*watcher,int status,int revents){
printf("on_disconnect.\n");
}
int main(){
	int ret;
	ssize_t slen;
	struct sockaddr_un addr;
	u=1;
	evfd=eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	if(evfd==-1){printf("evfd is -1\n");exit(EXIT_FAILURE);}else{printf("evfd is: %d\n",evfd);}
	
	
	data_socket=socket(AF_UNIX,SOCK_SEQPACKET | O_NONBLOCK,0);
	if(data_socket==-1){
	printf("data_socket err: %d\n",data_socket);
	perror("socket");
	close(evfd);
	exit(EXIT_FAILURE);
	}
	memset(&addr,0,sizeof(struct sockaddr_un));
	addr.sun_family=AF_UNIX;
	strncpy(addr.sun_path,socket_name,sizeof(addr.sun_path)-1);
	ret=connect(data_socket,(const struct sockaddr*)&addr,sizeof(struct sockaddr_un));
if(ret==-1){
fprintf(stderr,"the server is down.\n");
	close(evfd);
	close(data_socket);
	exit(EXIT_FAILURE);
}

	printf("gimme your inputs\n");
	slen=write(evfd,&u, sizeof(uint64_t));
	if(slen !=sizeof(uint64_t)){printf("!slen\n");close(evfd);close(data_socket);exit(EXIT_FAILURE);}else{printf("slen is ok\n");}
	uv_loop_t*loop=uv_default_loop();

	uv_poll_init(loop,&sockin_watcher, data_socket);
	uv_poll_init(loop,&sockout_watcher,data_socket);
	//uv_poll_init(loop,&disconnect_watcher,data_socket);
	uv_poll_init(loop,&stdin_watcher, evfd);
	
	
	uv_poll_start(&stdin_watcher,UV_READABLE, on_eventfd_read);
	//uv_poll_start(&disconnect_watcher,UV_DISCONNECT,on_disconnect);
	uv_run(loop,0);
	printf("**bye**\n");
	//uv_close((uv_handle_t*)&stdin_watcher,on_clo);
	close(evfd);
	close(data_socket);
	printf("***bye***\n");
return 0;
}