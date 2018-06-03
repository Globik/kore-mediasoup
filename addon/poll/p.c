//#include <node_api.h>
#include <string.h>
#include <stdio.h>//printf
#include <stdlib.h>
#include <unistd.h> // sleep
#include <poll.h>
#include <stdbool.h>
//#include <ee.h> // event emitter in C https://github.com/thlorenz/ee.c

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>

#include <signal.h>
//#include <uv_callback.h>
#include <sys/select.h>
#include <errno.h>

#include <fcntl.h>
#include <time.h>
#define socket_name "/home/globik/fuck"
#define buffer_size 512

int main(int argc,char*argv[]){
struct sockaddr_un addr;

	int i;int j;
	int rc=1;
	//int
		bool endserv=false;
	//int 
		bool closeconn,compressarray;
	int ret;
	int data_socket;
	char buffer[buffer_size];
	int timeout;
	size_t len;
	struct pollfd fds[0];
	int nfds=1;int current=0;
	data_socket=socket(AF_UNIX,SOCK_SEQPACKET | O_NONBLOCK,0);
	
	if(data_socket==-1){
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
	memset(fds,0,sizeof(fds));
	fds[0].fd=data_socket;
	fds[0].events=POLLIN;
	timeout=(1*60*1000);
	do{
	printf("waiting on poll\n");
		rc=poll(fds,nfds,timeout);
		if(rc<0){printf("poll failed\n");break;}
		if(rc==0){printf("tomeout\n");break;}
		current=nfds;
		for(i=0;i<current;i++){
		if(fds[i].revents==0)
			continue;
			if(fds[i].revents !=POLLIN){
			printf("error revents %d\n",fds[i].revents);
				endserv=true;
				break;
			}
			if(fds[i].fd==data_socket){
			printf("listening socket is readable\n");
				/*do{
				//accept
				}while();
				*/
			}else{
			printf("descriptor %d is readable\n",fds[i].fd);
				closeconn=false;
				do{
				rc=read(fds[i].fd, buffer,buffer_size);
					if(rc<0){
					if(errno !=EWOULDBLOCK){printf("receiver failed\n");closeconn=true;}
					break;
					}
					if(rc==0){printf("connection closed\n");closeconn=true;break;}
					len=rc;
					printf(" %d bytes received\n",len);
					rc=send(fds[i].fd,buffer,len,0);
					if(rc<0){printf("send failed\n");closeconn=true;break;}
				}while(true);
				if(closeconn){close(fds[i].fd);fds[i].fd=-1;compressarray=true;}
			}
		}
		if(compressarray){
		compressarray=false;
			for(i=0;i<nfds;i++){
			if(fds[i].fd==-1){
			for(j=i;j<nfds;j++){fds[j].fd=fds[j+1].fd;}
			nfds--;
			}
			}
		}
	}while(endserv=false);
	for(i=0;i<nfds;i++){
	if(fds[i].fd>=0)close(fds[i].fd);
	}
	return 0;
}
