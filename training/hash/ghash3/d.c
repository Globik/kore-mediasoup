#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
//#include <linux.h>
//#include <notifier.h>
//#include "/usr/src/linux-headers-3.13.0-143-generic/include/linux/notifier.h"
// /usr/src/linux-headers-3.13.0-143-generic/include/linux/notifier.h

//#include "/usr/src/linux-headers-3.2.0-23/include/linux/mutex.h"
//#include <glib.h>
//#include <linux/list.h> mmmm
#include <ee.h>
ee_t*ee=NULL;
const char*event_hello="hello";
//struct atomic_notifier_head *l;
//struct notifier_block*hn;
//struct foo*ld;
//atomic_notifier_chain_regiser(l,hn);
struct  media;
typedef void(*on_close)(struct media*,char*);
typedef void(*suka)(void*);
typedef void(*emitter)(suka, char*);
struct media{
	int a;
	on_close cb_close;
};
struct nota{
emitter emit;
};
void on_emitter(suka,char*);
void bsuka(void*);
void on_media_close(struct  media*,char*);
struct media*media_new(on_close,struct nota);
void notify(struct media*,char*);
void create_room(struct media*);
struct nota emi;

void on_added_new_listener(void*arg){
ee_new_listener_t*listener;
	listener=(ee_new_listener_t*)arg;
	printf("New listener added for event '%s'.\n",listener->name);
}

void on_hello(void*arg){
char*s=(char*)arg;
	printf("Invoked `on_hello` with '%s'\n",s);
}

int main(){
//struct nota emi;
	
	//ee_t*
		ee=ee_new();
	//ee_destroy(ee);
	//ee=NULL;
	if(ee==NULL)exit(1);
	ee_on(ee,EE_NEW_LISTENER,on_added_new_listener);
	printf("count listen: %d\n",ee_listener_count(ee,event_hello));
	//ee_on(ee,event_hello,on_hello);
	printf("count listen: %d\n",ee_listener_count(ee,event_hello));
	ee_emit(ee,event_hello," world");
	//ee_remove_listener(ee,event_hello,on_hello);
	printf("count listen: %d\n",ee_listener_count(ee,event_hello));
	
	

	printf("eee : %p\n",ee);
	emi.emit=on_emitter;
	
struct media*m=media_new(on_media_close, emi);
if(m==NULL)exit(1);
printf("zifr_1: %d\n",m->a);
notify(m,"room_created");
printf("zifr_2: %d\n",m->a);
notify(m,"room_closed");
printf("zifr_3: %d\n",m->a);
//atomic_notifier_chain_regiser(l,hn);
free(m);
ee_remove_listener(ee,event_hello,on_hello);
ee_destroy(ee);
return 0;
}
struct media*media_new(on_close cb,struct nota emi){
struct media*m=(struct media*)calloc(1,sizeof*m);
if(m==NULL)return NULL;
m->a=1;
m->cb_close=cb;//this.on("event",(data)=>{}) ???
//emi.emit("emitter runned.");
ee_on(ee,event_hello,on_hello);
return m;
}
// on_close proto
void on_media_close(struct media*m,char*s){
printf("on media close. event: %s\n",s);
m->a=2;
ee_emit(ee,event_hello,"fucker!!!!!!!");
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