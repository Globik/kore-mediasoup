// training/hash/ghash1
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
//gcc -o m m.c see makefile in this ghash directory

int refdebug=1;
#define j_refcount(refptr,type,member) \
((type*)((char*)(refptr) - offsetof(type,member)))

typedef struct j_refcnt j_refcnt;
struct j_refcnt{
	gint count;
	void(*free)(const j_refcnt*);
};

#define j_refcount_init(refp,free_fn){ \
if(!refdebug){ \
j_refcount_init_nodebug(refp,free_fn); \
}else{ \
j_refcount_init_debug(refp,free_fn); \
} \
}

#define j_refcount_init_debug(refp,free_fn){ \
(refp)->count=1; \
g_print("[%s:%s:%d:init] %p (%d)\n",__FILE__,__FUNCTION__,__LINE__, refp,(refp)->count); \
(refp)->free=free_fn; \
}

#define j_refcount_init_nodebug(refp, free_fn){ \
(refp)->count=1; \
(refp)->free=free_fn; \
}

#define j_refcount_inc(refp){ \
if(!refdebug){ \
j_refcount_increase_nodebug(refp); \
}else{ \
j_refcount_increase_debug(refp); \
} \
}
#define j_refcount_increase_nodebug(refp){ \
g_atomic_int_inc((gint*)&(refp)->count); \
}
#define j_refcount_increase_debug(refp){ \
g_print("[%s:%s:%d:increase] %p (%d)\n",__FILE__,__FUNCTION__,__LINE__, refp,(refp)->count+1); \
g_atomic_int_inc((gint*)&(refp)->count); \
}
#define j_refcount_dec(refp){ \
if(!refdebug){ \
j_refcount_decrease_nodebug(refp); \
}else{ \
j_refcount_decrease_debug(refp); \
} \
}
#define j_refcount_decrease_debug(refp){ \
g_print("[%s:%s:%d: decrease] %p (%d)\n",__FILE__,__FUNCTION__,__LINE__, refp, (refp)->count-1); \
if(g_atomic_int_dec_and_test((gint*)&(refp)->count)) { \
(refp)->free(refp); \
} \
}
#define j_refcount_decrease_nodebug(refp){ \
if(g_atomic_int_dec_and_test((gint*)&(refp)->count)){ \
(refp)->free(refp); \
} \
}

struct room;
typedef void(*on_open)(struct room*broom,void*d);
typedef void(*on_close)();

typedef struct
{
int a;
on_open open;
j_refcnt ref;
}channel;

struct room
{
int b;
on_close close;
};
//void do_free(j_refcnt*);
static void do_free(const j_refcnt*refp){
channel*ch=j_refcount(refp,channel, ref);
g_print("boo %p\n",ch);
	g_free(ch);
	ch=NULL;
	g_print(" p %p\n",ch);
}

channel * create_room(on_open cb, int b)
{
channel * ch = (channel*)calloc(1, sizeof * ch);
if(ch == NULL){
printf("channel calloc is null.\n");
return NULL;
}
ch->a = b;
ch->open = cb;
j_refcount_init(&ch->ref, do_free);
return ch;
}

void on_cb(struct room * vroom, void * d)
{
printf("OK\n");
printf("vroom->b: %d\n", vroom->b);
vroom->close();
}

void closed()
{
printf("closed?\n");
}

void on_remove(gpointer data)
{
printf("on_remove occured.%p\n", data);
channel * l = (channel*)data;
printf("data:%p %d\n",l,l->a);
j_refcount_dec(&l->ref);
//g_free(data);
//data = NULL;
//printf("end p %p\n", data);
}

int main()
{
printf("entering\n");
struct room broom;
broom.b = 1;
broom.close = closed;
channel * ch = create_room(on_cb, 10);
if(ch == NULL) exit(1);
ch->open(&broom, NULL);
printf("ch->a: %d\n", ch->a);
printf("p %p p_ref:  %p\n", ch,&ch->ref);
GHashTable * rooms=g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)on_remove);
	  g_hash_table_insert(rooms,"dummy_key", ch);
printf("there are %d keys in the hash.\n", g_hash_table_size(rooms));
channel * result = g_hash_table_lookup(rooms, "dummy_key");
if(result){
printf("FOUND! %p\n", result);
printf("result->a: %d\n", result->a);
result->open(&broom, NULL);
}else{
printf("NOT FOUND!\n");
free(ch);
g_hash_table_destroy(rooms);
exit(0);
}
gboolean foo = g_hash_table_remove(rooms, "dummy_key");
printf("the value 'dummy_key' was %s found and removed\n", foo ? "":"not");
printf("there are %d keys in the hash.\n", g_hash_table_size(rooms));
g_hash_table_destroy(rooms);
printf("end 2 p %p\n", ch);
printf("bye!***\n");
return 0;
}