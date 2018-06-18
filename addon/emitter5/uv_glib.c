//#include <errno.h>
//#include <fcntl.h>
//#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//#include <sys/socket.h>

#include <stdint.h>
//#include "uv_callback.h"
#include <glib.h>

//#include <sys/un.h>
//#include <sys/types.h>

#include <node_api.h>
#include <uv.h>
#define green "\x1b[32m"
#define rst "\x1b[0m"
#define red "\x1b[31m"
#define yel "\x1b[33m"

int count=5;
int abba=0;
GMainLoop*gloop;
static uv_async_t async_g;

void on_clo(uv_handle_t*h){
printf("ON_CLO\n");
}
gboolean cb(gpointer d){
printf(red "count: %d\n" rst,count);
printf(yel "abba: %d\n" rst,abba);
uv_async_send(&async_g);
if(--count==0){
printf("count: %d\n",count);
g_main_loop_quit(gloop);
return FALSE;
}
return TRUE;
}

static void *watcher(void*arg){
printf(green "watcher started.\n" rst);
	//exit(0);
gloop=g_main_loop_new(NULL,FALSE);
g_timeout_add(1000,cb,NULL);
printf("before gloop\n");
g_main_loop_run(gloop);
printf("after gloop\n");
g_main_loop_unref(gloop);
return 0;
}


void print_to(uv_async_t*h){
printf("print_to.\n");
abba++;
if(count==0)uv_close((uv_handle_t*)&async_g, on_clo);
}

static int start_watcher(){
static bool watcher_started=false;
	pthread_t thread_id;
	if(watcher_started)return 0;
	int err;
	err=uv_async_init(uv_default_loop(), &async_g, print_to);
	if(err<0) return -err;
	err=pthread_create(&thread_id,0,watcher,0);
	if(err !=0){
	uv_close((uv_handle_t*)&async_g,0);
	return err;
	}
	watcher_started=true;
	return 0;
}

napi_value p_create(napi_env env, napi_callback_info info)
{
napi_status k;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);
int err=start_watcher();
printf(red "err: %d\n" rst, err);
	
napi_value argv[1];

const char * str = "created!";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){printf(red "call_func p_create [result] is NOT OK!\n" rst);}
return NULL;
}

napi_value Init(napi_env env, napi_value exports)
{
//atexit(at_pexit);
	napi_status status;
	napi_value fn;//fn1;//,fn2,fn3,fn4;
	status=napi_create_function(env,NULL,0,p_create,NULL,&fn);
	if(status !=napi_ok){printf(red "create func p_create fail.\n" rst);return NULL;}
	status=napi_set_named_property(env,exports,"p_create",fn);
	if(status !=napi_ok){printf(red "set prop p_create fail.\n" rst);return NULL;}
	
	return exports;
}
NAPI_MODULE(addon,Init)