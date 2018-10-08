#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
//#include <glib.h>
//#include "ref_counter.h"
#include <lwan/lwan.h>
#include <ee.h>
struct server;

ee_t * bali=NULL;

typedef void(*on_emit)(struct server*,const char*,void*);
typedef void(*on_close)(struct server*);

typedef int(*on_done)(int,int);
typedef void(*on_create_something)(struct server*,int,on_done);
int func(struct coro*,void*);
struct fig{int b;};
struct server{
	ee_t*ee;
	struct fig f;
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

void on_dati(void*d){
printf("on_dati occured\n");
struct server*obj=(struct server*)d;
struct fig f=obj->f;
f.b=0;
int k;

//m.str=NULL;
//m.line=NULL;
struct coro_switcher switcher;


struct coro*coro=coro_new(&switcher,func, &f);


while((k=coro_resume(coro)))printf("*** K: ***: %d\n",k);	
//printf("coro data %s\n",f.line);
printf("coro ziffer: %d\n",f.b);
obj->f.b=f.b;
//return (void)m.b;
coro_free(coro);
}

int doni(int err,int result){
	if(err !=0){printf("err %d\n",err);return 1;}
	if(result !=0){printf("result: %d\n",result);return result;}
}

void create_somethingi(struct server*obj,int a, on_done doni){
if(a==100) {printf("a==100\n");doni(1,0);return;}	
printf("after a==100\n");

ee_on(obj->ee,"data",on_dati);

doni(0,300);
return;
}
void*mus(struct server*obj,on_done doni){
	printf("WITHIN MUS()\n");
	doni(3333,4444);
	}
void *as(struct server*obj){
return	mus(obj,doni);
	}
void suki(void*d){
	//printf("suki: %s\n",(char*)d);
	//printf("suki: %d\n",(int)d);
	//sleep(4);
	//ee_on(bali,"freund",void m(d
	}
int func(struct coro*coro,void*data){
	
	
	struct fig *f=(struct fig*)data;
	int b=f->b;
printf("within coro func, data: %d \n",b);
//sleep(10);

//f->line=coro_malloc(coro,5);
//->line="suka\0";

f->b=505;

coro_defer(coro,suki,as);
coro_yield(coro,1);

 
coro_yield(coro,0);
__builtin_unreachable();	
	}
int main(){
ee_t*ee=ee_new();
if(ee==NULL)return 0;
bali=ee;
struct server*server=server_new(ee);
if(server==NULL){
ee_destroy(ee);
return 0;
}
//int k;
struct fig f;
ee_on(server->ee,"close", on_close_cb);
int ds=(int)as(server);
printf("DS: %d\n",ds);
server->create_something(server,101,doni);
printf("serveriii %d\n",server->f.b);
server->emit(server,"data",server);

printf("serveriii %d\n",server->f.b);
server->close(server);

printf("serveriii %d\n",server->f.b);

ee_destroy(ee);	
printf("serveriii 555555555555555 %d\n",server->f.b);
free(server);
server=NULL;

if(server){
printf("serveriii  6666666666666666666 , %d\n",server->f.b);
}
printf("server: %p\n",server);
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
struct fig f;
f.b=0;
obj->ee=ee;
obj->emit=emiti;
obj->close=closi;
obj->f=f;
obj->create_something=create_somethingi;
return obj;
}

void closi(struct server*obj){
printf("closi occured\n");
struct out_data data;
data.str="someone closes the server.";
printf("serveriii WITHIN CLOSI %d\n",obj->f.b);
obj->emit(obj,"close",(void*)&data);
}
