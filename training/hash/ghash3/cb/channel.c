#include "channel.h"
static void channel_send(struct channel*, char*);
static void invoke_for_dummy(struct channel*);
static void on_erst_data(void*);
static const char*erste_data="erste_data";
static const char*zweite_data="zweite_data";

struct responsi{
struct channel*ch;
void*data;
};

struct channel*channel_new(){
struct channel*ch=NULL;
ch=malloc(sizeof(struct channel));
if(ch==NULL)return NULL;
ch->ee=NULL;
ch->request=channel_send;
return ch;	
}

void channel_send(struct channel*ch, char*str){
printf("channel_send occured\n");
ee_once(ch->ee, erste_data, on_erst_data);
invoke_for_dummy(ch);
}
void on_erst_data(void*data){
printf("on_erst_data\n");
struct responsi *resp=(struct responsi*)data;
printf("here data: %s\n",(char*)resp->data);
// accepted, rejected, targetId
//if (accepted)
ee_emit(resp->ch->ee, zweite_data, "accepted with data if any");
}
void invoke_for_dummy(struct channel*ch){
//if(dummy_result)
//dummy_result(ch,"room created");
struct responsi resp;
resp.ch=ch;
resp.data="room_created";
ee_emit(ch->ee, erste_data, (void*)&resp);
// the same as on_req_cb req_cb; need to store in some hash table
// for later use in response from a thread
}
