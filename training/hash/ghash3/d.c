#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
#include "ref_counter.h"

#include <ee.h>
ee_t*ee=NULL;
const char*event_hello="hello";
struct  media;struct room;
typedef void(*on_close)(struct media*,char*);
typedef int(*proto_create_room)(struct media*,char*);
typedef void(*proto_on_new_room)(struct media*,char*);
typedef void(*suka)(void*);
typedef void(*emitter)(suka, char*);
typedef struct room*(*proto_get_room)(struct media*,gint);
typedef void(*proto_close_room)(struct media*,gint);
//typedef 
struct media{
	int a;
	on_close cb_close;
	proto_create_room create_room;
	proto_on_new_room on_new_room;
	proto_get_room get_room;
	proto_close_room close_room;
	GHashTable *rooms;
	j_refcnt ref;
	};
struct media *me=NULL;
struct nota{
emitter emit;
};
struct room{
int a;
gint b;
j_refcnt ref;
};
gint vid=0;
void on_emitter(suka,char*);
void bsuka(void*);
void on_media_close(struct  media*,char*);
struct media*media_new(on_close,proto_on_new_room,struct nota);
void notify(struct media*,char*);

int create_room(struct media*,char*);
void on_new_Room(struct media*,char*);
struct room*room_new(void);
//void create_room(struct media*);
struct nota emi;

void on_added_new_listener(void*arg){
ee_new_listener_t*listener;
listener=(ee_new_listener_t*)arg;
printf("New listener added for event '%s'.\n",listener->name);
}

void on_room_remove(gpointer data)
{
printf("on_room_remove occured.\n");

struct room * r = (struct room*)data;
if(!r)return;
printf("data:%p %d\n",r,r->a);
j_refcount_dec(&r->ref);
}

void add_room_to_media(struct media*m, struct room*r){
if(m==NULL || r==NULL)return;
printf("adding room to media\n");
if(m->rooms==NULL){
m->rooms=g_hash_table_new_full(g_int_hash, g_int_equal, NULL, (GDestroyNotify)on_room_remove);
}
	// int a = 0 int key=g_new0(gint,1) *key=tmp; insert(key);
g_hash_table_insert(m->rooms,&(r->b), r);
m->on_new_room(m,"new room!!!!!\n");
/*
struct room * result = g_hash_table_lookup(m->rooms, &(r->b));
if(result){
printf("ROOM FOUND! %p\n", result);
printf("result->a: %d\n", result->a);
}else{
printf("ROOM NOT FOUND!\n");
}
*/
}

void on_hello(void*arg){
char*s=(char*)arg;
printf("Invoked `on_hello` with '%s'\n",s);
if(!strcmp(s,"room_create")){
printf("from channel: 'room_create'.\n");
struct room*r=NULL;
	   r=room_new();
if(r==NULL){printf("room is null\n");return;}
printf("r-> %d\n",r->a);
add_room_to_media(me,r);
}
}

int main(){
ee=ee_new();
if(ee==NULL)exit(1);
ee_on(ee,EE_NEW_LISTENER,on_added_new_listener);
	printf("count listen: %d\n",ee_listener_count(ee,event_hello));
	ee_on(ee,event_hello, on_hello);
	printf("count listen: %d\n",ee_listener_count(ee,event_hello));
	//ee_emit(ee,event_hello," world");
	//ee_remove_listener(ee,event_hello,on_hello);
	printf("count listen: %d\n",ee_listener_count(ee,event_hello));
	
	

	printf("eee : %p\n",ee);
	emi.emit=on_emitter;
	
//struct media*
me=media_new(on_media_close,on_new_Room, emi);
if(me==NULL)exit(1);
printf("zifr_1: %d\n",me->a);
int j=me->create_room(me,"create_room");
printf("cr room?: %d\n",j);
printf("get the room from media.\n");
printf("there are %d keys in the hash.\n", g_hash_table_size(me->rooms));
struct room *r=me->get_room(me, 1);
if(r==NULL){
printf("THE ROOM IS NULL OR NOT FOUND!!!\n");
}else{
printf("THE ROOM IS NOT NULL AND FOUND!!!\n");
printf("room->a from media %d\n",r->a);
printf("room->b from media %d\n",r->b);
}
int j2=me->create_room(me,"create_room");
	printf("j2 %d\n",j2);
printf("there are %d keys in the hash.\n", g_hash_table_size(me->rooms));
	printf("get the room from media.\n");
	struct room *r2=me->get_room(me, 2);
if(r2==NULL){
printf("THE ROOM_2 IS NULL OR NOT FOUND!!!\n");
}else{
printf("THE ROOM_2 IS NOT NULL AND FOUND!!!\n");
printf("room2->a from media %d\n",r2->a);
printf("room2->b from media %d\n",r2->b);
}
printf("\nSLEEP\n");
sleep(1);
me->close_room(me,2);
me->close_room(me,1);
//free(r);
//free(m);
	printf("\nSLEEP\n");
	sleep(1);
j_refcount_dec(&me->ref);
ee_remove_listener(ee,event_hello,on_hello);
ee_destroy(ee);
return 0;
}

int create_room(struct media*m,char*s)
{
if(m==NULL){printf("is null\n");return -1;}
printf("creating a room. : %s\n",s);

//notify(m,"room_created - success");
ee_emit(ee, event_hello,"room_create");
return 0;
}
void on_new_Room(struct media*m,char*s)
{
	printf("on new room. : %s\n",s);
	//printf(
}
static void destroy_media(const j_refcnt*refp)
{
g_print("Trying destroy  media.\n");
struct media*m=j_refcount(refp,struct media, ref);

g_print("boo %p\n",m);
if(m->rooms !=NULL){
//j_refcount_dec(&m->rooms->ref);
g_hash_table_destroy(m->rooms);
}
m->rooms=NULL;
free(m);
m=NULL;
g_print(" p in media %p\n", m);
}

static void destroy_room(const j_refcnt*refp)
{
g_print("Trying destroy room.\n");
struct room*r=j_refcount(refp,struct room, ref);
	if(!r && r==NULL)return;
	if(ee)	ee_emit(ee,event_hello,"room_closed");

free(r);
r=NULL;
}
struct room*get_room(struct media*m,gint vint){
if(!vint)return;
struct room*r=NULL;
if(m!=NULL){
r = g_hash_table_lookup(m->rooms, &(vint));
if(r){
printf("ROOM FOUND! %p\n", r);
printf("result->a: %d\n", r->b);
return r;
}else{
printf("ROOM NOT FOUND!\n");
}
}
return r;
}
void close_room(struct media*m, gint vint)
{
if(m==NULL)return;
if(m->rooms==NULL)return;
gboolean foo = g_hash_table_remove(m->rooms, &(vint));
printf("the value 'dummy_key' was %s found and removed\n", foo ? "":"not");
printf("there are %d keys in the hash.\n", g_hash_table_size(m->rooms));
//if(ee)	ee_emit(ee,event_hello,"room_closed");
}

struct media * media_new(on_close cb, proto_on_new_room on_new_room_cb, struct nota emi){
struct media * m=(struct media*)calloc(1,sizeof*m);
if(m==NULL){printf("m is null\n");return NULL;}
printf("MEDIA p %p\n",m);
m->a=1;
m->rooms=NULL;
m->cb_close=cb;//this.on("event",(data)=>{}) ???
m->create_room=create_room;

m->get_room=get_room;
m->close_room=close_room;
m->on_new_room=on_new_room_cb;

j_refcount_init(&m->ref, destroy_media);
return m;
}
struct room*room_new(){
struct room*r=(struct room*)calloc(1,sizeof*r);
if(r==NULL)return NULL;
vid++;
r->b=vid;
r->a=10;
j_refcount_init(&r->ref, destroy_room);
return r;
}
// on_close proto
void on_media_close(struct media*m,char*s){
printf("on media close. event: %s\n",s);
m->a=2;
	//room created success notify client
m->on_new_room(m,"ROOM CREATED!");
//ee_emit(ee,event_hello,"fucker!!!!!!!");
//emi.emit(bsuka,"closed");
//ee_emit(ee,event_hello,"fucker!");
}
void notify(struct media*m,char*s){
printf("notify.\n");
m->cb_close(m,s);//this.emit(ev,data)
//emi.emit("fuck");
}
void on_emitter(suka bsuka, char*s){
printf("on emitter. String: %s\n",s);
bsuka(s);
}
void bsuka(void*d){
printf("on suka.\n");
}