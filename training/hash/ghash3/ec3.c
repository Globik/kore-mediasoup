#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
//#include <glib.h>
//#include "ref_counter.h"

#include <ee.h>
struct server;
struct channel;
typedef void(*on_emit)(struct server*,const char*,void*);
typedef void(*on_close)(struct server*);
typedef void(*on_req_cb)(struct channel*,char*);
typedef void(*on_channel_send)(struct channel*,char*, on_req_cb);
typedef void(*on_response_channel)(char*);
typedef void(*on_notify)(char*);

typedef int(*on_funny)();
typedef int(*on_create_something)(struct server*,int,on_funny);


struct channel{
ee_t*ee;
on_channel_send request;
on_notify notify;
};
struct responsi{
	struct channel*ch;
	void*data;
	};
struct server{
	ee_t*ee;
	struct channel*ch;
	on_emit emit;
	on_close close;
	on_create_something create_something;
	on_funny on_fun;
	
};
on_req_cb dummy_result=NULL;
const char*erst_data="erst_data";
const char*zweite_data="zweite_data";
void notifier(char * a){
printf("notifier(), data came: %s\n",a);
//on_fun("a");	
}

int on_funi(){
printf("on_fun()\n");
return 0;
}
void on_erst_data(void*data){
	printf("on_erst_data\n");
	struct responsi *resp=(struct responsi*)data;
	printf("here data: %s\n",(char*)resp->data);
	// accepted, rejected, targetId
//if (accepted)
	ee_emit(resp->ch->ee, zweite_data, "accepted with data");//or empty data or rejected or targetid
}

void on_zweite_data(void*data){
printf("on_zweite_data: %s\n",(char*)data);
//here create a room instance
on_funi();//??
	
}
void invoke_for_dummy(struct channel*ch){
//if(dummy_result)
//dummy_result(ch,"room created");
struct responsi resp;
resp.ch=ch;
resp.data="room_created";
ee_emit(ch->ee, erst_data, (void*)&resp);
// the same as on_req_cb req_cb; need to store in some hash table
// for later use in response from a thread


}
void req_cb(struct channel*s, char*str){
printf("req_cb()\n");	
s->notify("kuku");
// if 
}

void channel_send(struct channel*ch, char*str, on_req_cb req_cb){
printf("channel_send occured\n");
// need a new Map() as in js	
dummy_result = req_cb;
ee_once(ch->ee, erst_data, on_erst_data);
invoke_for_dummy(ch);
}

struct out_data{
const char*str;	
};
struct channel*channel_new();
struct server*server_new(ee_t*,struct channel*);
void on_close_cb(void*);
void closi(struct server*);


int create_somethingi(struct server * server, int a, on_funny on_funi){
printf("in create_somethingi()\n");
ee_once(server->ch->ee, zweite_data, on_zweite_data);//on accepted with data if any, rejected
server->ch->request(server->ch,"create_room", req_cb);
return 0;
}

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

ee_on(server->ee, "close", on_close_cb);

server->create_something(server,101, on_funi);

server->close(server);
free(ch);
server->ch=NULL;
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
struct server*server_new(ee_t*ee,struct channel*ch){
if(ch==NULL)return NULL;
struct server*obj=NULL;
obj=/*(struct server*)*/malloc(sizeof(struct server));
if(obj==NULL)return NULL;
obj->ee=ee;
obj->ch=ch;
ch->ee=obj->ee;
obj->emit=emiti;
obj->close=closi;
obj->create_something=create_somethingi;
obj->on_fun=NULL;
//obj->on_funny=funny;
//obj->doni=doni;
return obj;
}

struct channel*channel_new(){
struct channel*ch=NULL;
ch=/*(struct channel*)*/malloc(sizeof(struct channel));
if(ch==NULL)return NULL;
ch->ee=NULL;
ch->request=channel_send;
ch->notify=notifier;
return ch;	
}

void closi(struct server*obj){
printf("closi occured\n");
struct out_data data;
data.str="someone closes the server.";
obj->emit(obj,"close",(void*)&data);
}
