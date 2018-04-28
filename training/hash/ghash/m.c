// training/hash/ghash
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
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

GHashTable * booms;
struct room mk;
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
void bamus(gpointer data){printf("bamus.%p\n",data);
						  chan*l=(chan*)data;
						  printf("data:%d\n",l->a);
						 g_free(data);
						  data=NULL;
						  printf("end p %p\n",data);
						 }
int main(){
printf("entering\n");
struct room br;
br.b=1;
br.close=closed;
//struct 
	chan *cu=create_room(on_koo,10);
	if(cu==NULL)exit(1);
	cu->on_op(&br,NULL);
	printf("cu->a: %d\n",cu->a);
	printf("p %p\n",cu);
	booms=g_hash_table_new_full(g_str_hash,g_str_equal,NULL,(GDestroyNotify)bamus);
	g_hash_table_insert(booms,"suka",cu);
	//free(cu);
	printf("there are %d keys in the hash.\n",g_hash_table_size(booms));
	//free(cu);
	chan * lu=g_hash_table_lookup(booms,"suka");
	if(lu){
	printf("FOUND! %p\n",lu);
		printf("lu->a: %d\n",lu->a);
		lu->on_op(&br,NULL);
	}else{printf("NOT FOUND!\n");}
	gboolean fu=g_hash_table_remove(booms,"suka");
	printf("the value 'suka' was %s found and removed\n",fu ? "":"not");
	printf("there are %d keys in the hash.\n",g_hash_table_size(booms));
	
	g_hash_table_destroy(booms);
	//g_free(cu);
	printf("end 2 p %p\n",cu);


return 0;
}