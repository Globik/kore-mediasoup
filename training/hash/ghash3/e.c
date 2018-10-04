// https://www.codeproject.com/Articles/108830/Inheritance-and-Polymorphism-in-C
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
//#include <glib.h>
//#include "ref_counter.h"

#include <ee.h>
struct s_class;
typedef void(*emit_was)(struct s_class*);

struct s_class{
ee_t *ee;
void*subi_data;
emit_was dura;
};

struct sub_class{
struct s_class subi;
//emit_was dura;
int b;	
};

void semit(struct s_class*t){
printf("what the fuck?\n");	
}

struct s_class*base_class_new(int a){
	struct s_class*obj=NULL;
	obj=(struct s_class*)malloc(sizeof(struct s_class));
	if(obj==NULL)return NULL;
	//struct sub_class*su=(struct sub_class*)malloc(sizeof(struct sub_class));
	//if (su==NULL){free(obj);return NULL;}
	ee_t *ee=ee_new();
	if(ee==NULL){free(obj);return NULL;}
	obj->ee=ee;
	obj->dura=semit;
	obj->subi_data=obj;
	return obj;
	
}
struct s_class*new_subclass(
void main_free(struct s_class*m){
if(m==NULL)return;
//if(m->subi_data){free(m->subi_data);m->subi_data=NULL;}
m->subi_data=NULL;
if(m->ee)ee_destroy(m->ee);
free(m);	
printf("end of main_free\n");
}
int main(){
	struct s_class*obj=base_class_new(2);
	if(obj==NULL)return 0;
	obj->dura(obj);
	main_free(obj);
return 0;	
}
