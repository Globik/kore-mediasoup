#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
//#include <glib.h>
//#include "ref_counter.h"

#include <ee.h>
struct server;
typedef void(*on_emit)(struct server*,const char*,void*);
typedef void(*on_close)(struct server*);

typedef int(*on_done)(struct server*,int,int);
typedef int(*on_funny)();
typedef int(*on_create_something)(struct server*,int,on_funny);

on_funny assa;
ee_t *bala=NULL;
struct server{
	ee_t*ee;
	on_emit emit;
	on_close close;
	on_create_something create_something;
	on_done doni;
};
struct out_data{
const char*str;	
};
struct server*server_new(ee_t*);
void on_close_cb(void*);
void closi(struct server*);
void response(){
printf("The response just came.\n");
assa();

	}
int on_funn(){
	printf("IN_ON_FUNN()\n");
	return 1;
	}
void send(char*a,on_funny on_funn){
printf("sendig request.\n");
	//ee_emit(bala,"OK","ass");
assa=on_funn;	
response();
	}
int donis(struct server*s,int err,int result){
	printf("IN ON DONI()\n");
	if(err !=0){printf("err %d\n",err);return 1;}
	if(result !=0){printf("result: %d\n",result);
	return result;
}
}

int create_somethingi(struct server*server,int a, on_funny on_funn){
printf("now sending request\n");
send("some_data",on_funn);
return 88;
}

int main(){
ee_t*ee=ee_new();
if(ee==NULL)return 0;
bala =ee;
struct server*server=server_new(ee);
if(server==NULL){
ee_destroy(ee);
return 0;
}
ee_on(server->ee,"close", on_close_cb);
int something_error=server->create_something(server,101,on_funn);
//suka();
printf("somthing_error: %d\n",something_error);
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
//obj->doni=doni;
return obj;
}

void closi(struct server*obj){
printf("closi occured\n");
struct out_data data;
data.str="someone closes the server.";
obj->emit(obj,"close",(void*)&data);
}
