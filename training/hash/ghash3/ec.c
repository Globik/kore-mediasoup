#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
//#include <glib.h>
//#include "ref_counter.h"

#include <ee.h>
struct server;
typedef void(*on_emit)(struct server*,const char*,void*);
typedef void(*on_close)(struct server*);

typedef int(*on_done)(int,int);
typedef void(*on_create_something)(int,on_done);

struct server{
	ee_t*ee;
	on_emit emit;
	on_close close;
	on_create_something create_something;
};
struct out_data{
const char*str;	
};
struct server*server_new(ee_t*);
void on_close_cb(void*);
void closi(struct server*);

int doni(int err,int result){
	if(err !=0){printf("err %d\n",err);return 1;}
	if(result !=0){printf("result: %d\n",result);return result;}
}

void create_somethingi(int a, on_done doni){
if(a==100) {printf("a==100\n");doni(1,0);return;}	
printf("after a==100\n");
doni(0,300);
return;
}

int main(){
ee_t*ee=ee_new();
if(ee==NULL)return 0;
struct server*server=server_new(ee);
if(server==NULL){
ee_destroy(ee);
return 0;
}
ee_on(server->ee,"close", on_close_cb);
server->create_something(101,doni);
server->close(server);
ee_destroy(ee);	
free(server);
printf("*** bye ***\n");
return 0;
}
void emiti(struct server*server,const char*str,void*data){
ee_emit(server->ee, str, data);	
}
		
void on_close_cb(void*data){
//printf("on_close_cb occured. Data: %s\n",(char*)data);
struct out_data*d=(struct out_data*)data;
printf("on_close_cb occured.\n");
printf("DATA: %s\n",d->str);

}
struct server*server_new(ee_t*ee){
struct server*obj=NULL;
obj=(struct server*)malloc(sizeof(struct server));
if(obj==NULL)return NULL;
obj->ee=ee;
obj->emit=emiti;
obj->close=closi;
obj->create_something=create_somethingi;
return obj;
}

void closi(struct server*obj){
printf("closi occured\n");
struct out_data data;
data.str="someone closes the server.";
obj->emit(obj,"close",(void*)&data);
}
