
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "mediasoup.h"
void on_close_cb(void*);
int on_funi(void);

int main(){
ee_t*ee=ee_new();
if(ee==NULL)return 0;
struct channel*ch=channel_new();
if(ch==NULL){
ee_destroy(ee);
return 0;
}
struct server*server=server_new(ee,ch);
if(server==NULL){
ee_destroy(ee);
return 0;
}
ee_on(server->ee,"close", on_close_cb);

server->create_something(server,101,on_funi);

server->close(server);
free(ch);
server->ch=NULL;
ee_destroy(ee);	
free(server);
printf("*** bye ***\n");
return 0;
}
void on_close_cb(void*data){
struct out_data*d=(struct out_data*)data;
printf("on_close_cb occured.\n");
printf("DATA: %s\n",(char*)d->str);

}
int on_funi(){
printf("on_funi\n");
return 0;	
}
