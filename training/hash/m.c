#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "uthash.h"
//gcc -o m m.c
struct room;
//struct chan;
typedef void(*on_open)(struct room*broom,void*d);
typedef void(*on_close)();

typedef struct{
int a;
on_open on_op;
}chan;
struct room{
int b;
on_close close;
};
typedef struct{
chan key;
UT_hash_handle hh;
}record;
//struct 
	chan*create_room(on_open on_k,int b){
//struct 
	chan*g=(chan*)calloc(1,sizeof*g);
if(g==NULL){printf("g is null. exit.\n");return NULL;}
g->a=b;
g->on_op=on_k;
return g;
}
void on_koo(struct room*bt,void*d){
printf("OK\n");
printf("bt->b: %d\n",bt->b);
bt->close();
bt->close();
}
void closed(){printf("closed?\n");}
int main(){
printf("entering\n");
record l,*p,*r,*tmp,*records=NULL;
struct room br;
br.b=1;
br.close=closed;
//struct 
	chan *cu=create_room(on_koo,10);
	if(cu==NULL)exit(1);
	cu->on_op(&br,NULL);
	printf("cu->a: %d\n",cu->a);
	r=(record*)malloc(sizeof(record));
	if(r==NULL)exit(1);
	memset(r,0,sizeof(record));
	r->key.a=cu->a;
	r->key.on_op=cu->on_op;
	HASH_ADD(hh,records,key,sizeof(chan),r);
	free(cu);
	
	
memset(&l,0,sizeof(record));
l.key.a=10;
l.key.on_op=cu->on_op;
HASH_FIND(hh,records,&l.key,sizeof(chan),p);
	if(p){
		printf("found %d\n",p->key.a);
		p->key.on_op(&br,NULL);
	}else{printf("NOT found.\n");}
	//free(cu);
	HASH_ITER(hh,records,p,tmp){
	HASH_DEL(records,p);
		free(p);
	}
exit(0);
}