// training/hash/ghash
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>
//gcc -o m m.c see makefile in this ghash directory
struct room;
typedef void(*on_open)(struct room*broom,void*d);
typedef void(*on_close)();

typedef struct
{
int a;
on_open open;
}channel;

struct room
{
int b;
on_close close;
};

channel * create_room(on_open cb, int b)
{
channel * ch = (channel*)calloc(1, sizeof * ch);
if(ch == NULL){
printf("channel calloc is null.\n");
return NULL;
}
ch->a = b;
ch->open = cb;
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
printf("data:%d\n",l->a);
g_free(data);
data = NULL;
printf("end p %p\n", data);
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
printf("p %p\n", ch);
GHashTable * rooms = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify)on_remove);
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