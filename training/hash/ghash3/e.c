// https://www.codeproject.com/Articles/108830/Inheritance-and-Polymorphism-in-C
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
//#include <glib.h>
//#include "ref_counter.h"

#include <ee.h>
struct s_class;
struct sub_class;
const char*hell="hello";

typedef void(*emit_was)(struct s_class*);
typedef void(*cleanup)(struct s_class*);
typedef void(*on_hello)(void*);
typedef void(*on_emit)(struct sub_class*,const char*);

struct s_class{
//ee_t *ee;
void*subi_data;
emit_was dura;
cleanup clean;
//on_emit emit;
};

struct sub_class{
ee_t*ee;
struct s_class *subi;
on_hello onHello;
on_emit emit;
int b;	
};
void on_hellos(void*cl){
printf("on_hello occured  %s\n",(char*)cl);	
}
void on_emiti(struct sub_class*obj,const char*event_hello){
	printf("in emiti\n");
ee_emit(obj->ee, event_hello,"fucker!");
}
void semit(struct s_class*t){
printf("what the fuck? %p\n",t);	
}
void cleanupi(struct s_class*obj){
if(obj==NULL)return;
//if(obj->subi_data)free(subi_data);
//obj->subi_data=NULL;
//if(obj->ee){printf("there is ee\n");}
//ee_destroy(obj->ee);

free(obj);	
}
struct s_class*base_class_new(int a){
	struct s_class*obj=NULL;
	obj=(struct s_class*)malloc(sizeof(struct s_class));
	if(obj==NULL)return NULL;
	//struct sub_class*su=(struct sub_class*)malloc(sizeof(struct sub_class));
	//if (su==NULL){free(obj);return NULL;}
	//ee_t *ee=ee_new();
	//if(ee==NULL){free(obj);return NULL;}
	
	//obj->ee=NULL;//ee;
	//ee_on(obj->ee,"hello",on_hellos);
	obj->dura=semit;
	obj->subi_data=obj;
	obj->clean=cleanupi;
	//obj->emit=on_emiti;
	//obj->emit(obj,hell);
	
	return obj;
	
}
struct s_class*new_subclass(ee_t*ee){
struct s_class*pobj=base_class_new(1);
if(pobj==NULL)return NULL;
//ee_on(pobj->ee,hell,on_hellos);
struct sub_class*su=(struct sub_class*)malloc(sizeof(struct sub_class));
if (su==NULL){pobj->clean(pobj);return NULL;}
su->b=9;
su->subi=NULL;
su->onHello=on_hellos;
su->ee=ee;
su->emit=on_emiti;
pobj->subi_data=su;
pobj->clean=cleanupi;
//pobj->clean2=cl;
pobj->dura=semit;

//pobj->emit(pobj,"hello");
//pobj->emit=on_emit;
ee_on(su->ee,hell,on_hellos);
return pobj;
}

int main(){
	ee_t * ee=ee_new();
	if(ee==NULL)return 0;
	struct s_class*obj=base_class_new(2);
	if(obj==NULL)return 0;
	//ee_on(obj->ee,hell,on_hellos);
	struct s_class*su=new_subclass(ee);
	if(su==NULL){obj->clean(obj);return 0;}
	//obj->dura(obj);
	//su->dura(su);
	//printf("event: %p\n",obj->ee);
	//printf("event %p\n",su->ee);
	//su->emit(su,"hello");
	//ee_on(su->ee,hell,on_hellos);
	struct sub_class*nu=(struct sub_class*)su->subi_data;
	
	printf("int b: %d\n",nu->b);
	nu->emit(nu,"hello");
	//free(su->subi_data);
	//ee_on(obj->ee,hell,on_hellos);
	//su->emit(su,"hello");
	free(nu);
	su->clean(su);
	obj->clean(obj);
	ee_destroy(ee);
	printf("*** bye ***\n");
return 0;	
}
