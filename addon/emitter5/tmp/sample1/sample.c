// it's basic concept. To hack janus webRTC gateway properly.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//usleep
#include <pthread.h>

#include <node_api.h>
#include <uv.h>

#include "plugin.h"
#include "helper.h"
#define green "\x1b[32m"
#define yellow "\x1b[33m"
#define red "\x1b[31m"
#define rst "\x1b[0m"

static uv_async_t async_g;

static GMainContext *sess_watchdog_ctx=NULL;
j_plugin * janus_plugin=NULL;

int j_plugin_push_event(j_plugin*plugin,const char*transaction);

static j_cbs j_handler_plugin={
.push_event=j_plugin_push_event,
};
volatile gint stop=0;

gint stop_signal=0;

void on_clo(uv_handle_t*h){
printf("[sample.c]: on_uv_close handler.\n");
}
void print_to(uv_async_t*h){
printf("[sample.s]: print_to.\n");
//abba++;
//if(count==0)
uv_close((uv_handle_t*)&async_g, on_clo);
}
static void j_termination_handler(void) {
g_print("[sample.c]: At exit handler occured.\n");
}

int j_plugin_push_event(j_plugin *plugin, const char*transaction){
if(!plugin){ printf(red "plugin is -1\n" rst);return -1;}
printf(green "[sample.c]: The message came from echo plugin: %s\n" rst,transaction); 
return 0;
}


void j_handle_signal(int signum) {
	stop_signal = signum;
	switch(g_atomic_int_get(&stop)) {
		case 0:
			g_print("\n[sample.c]: Stopping gateway, please wait...\n");
			//uv_close((uv_handle_t*)&async_g, on_clo);
			break;
		case 1:
			g_print("[sample.c]: In a hurry? I'm trying to free resources cleanly, here!\n");
			break;
		default:
			g_print("[sample.c]: Ok, leaving immediately...\n");
			break;
	}
	
	g_atomic_int_inc(&stop);
	if(g_atomic_int_get(&stop) > 2) {
		g_print("[sample.c]: Here must be exit(0).\n");
		exit(0);
	}
		
}

static void * watcher(void * arg){
signal(SIGINT, j_handle_signal);
//signal(SIGTERM, j_handle_signal);
//atexit(j_termination_handler);
printf(green "[sample.c]: Setup Glib.\n" rst);
sess_watchdog_ctx=g_main_context_new();
GMainLoop *watchdog_loop=g_main_loop_new(sess_watchdog_ctx,FALSE);
GError *err=NULL;
GThread *watchdog=g_thread_try_new("sess",&j_sess_watchdog,watchdog_loop,&err);
if(err !=NULL){
printf(red "[sample.c]: Fatal err trying to start sess watchdog.\n" rst);
exit(1);
}
	
janus_plugin =(j_plugin*) plugin_create();
//create_p();// for dlopen
if(!janus_plugin) {
printf(red "[sample.c]: Couldn't use function 'plugin_create'...\n" rst);
}
if(!janus_plugin->init || !janus_plugin->destroy ||!janus_plugin->handle_message ) {
printf(red "[sample.c]: Missing some mandatory methods/callbacks, skipping this plugin...\n" rst);
}
if(janus_plugin->init(&j_handler_plugin) < 0) {
printf(red "[sample.c]: The  plugin could not be initialized.\n" rst);
}
	
j_plugin_res *resu=janus_plugin->handle_message("PING!");
if(resu==NULL){printf(yellow "[sample.c]: resu is null\n" rst);}
if(resu->type==J_PLUGIN_OK){printf("[sample.c]: j_plugin_ok\n");}
if(resu->type==J_PLUGIN_OK_WAIT){printf("[sample.c]: resu->type=> %s\n",resu->text);}
//int res=gw->push_event(&p_m,"Fucker"); in echo.c plugin
j_plugin_res_destroy(resu);
	
while(!g_atomic_int_get(&stop)){
usleep(250000);
}
	
g_print(green "[sample.c]: Ending watchdog loop.\n" rst);
g_main_loop_quit(watchdog_loop);
g_thread_join(watchdog);
watchdog=NULL;
g_main_loop_unref(watchdog_loop);
g_main_context_unref(sess_watchdog_ctx);
sess_watchdog_ctx=NULL;
if(janus_plugin !=NULL) {janus_plugin->destroy();janus_plugin=NULL;}
g_print("[sample.c]: ***Bye!***\n");
//uv_close((uv_handle_t*)&async_g, on_clo);
	uv_async_send(&async_g);
return 0;
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
if(err==0){
printf(yellow "[sample.c]: Thread with a glib loop created! %d\n" rst, err);
}else{
printf(red "[sample.c]: Failed to create a thread with a glib loop! %d\n" rst, err);
}
	
napi_value argv[1];

const char * str = "created!";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){printf(red "[sample.c]: Call_func p_create [result] is NOT OK!\n" rst);}
return NULL;
}

napi_value Init(napi_env env, napi_value exports)
{
//atexit(j_termination_handler);
	napi_status status;
	napi_value fn;//fn1;//,fn2,fn3,fn4;
	status=napi_create_function(env,NULL,0,p_create,NULL,&fn);
	if(status !=napi_ok){printf(red "create func p_create fail.\n" rst);return NULL;}
	status=napi_set_named_property(env,exports,"p_create",fn);
	if(status !=napi_ok){printf(red "set prop p_create fail.\n" rst);return NULL;}
	
	return exports;
}
NAPI_MODULE(addon,Init)