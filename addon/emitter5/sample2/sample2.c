// it's basic concept. To hack janus webRTC gateway properly.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//usleep
#include <pthread.h>
#include <signal.h>

#include <dlfcn.h>
#include <dirent.h>
#include <net/if.h>
#include <netdb.h>
#include <sys/resource.h>
#include <sys/stat.h>

#include <node_api.h>
#include <uv.h>

#include "plugin.h"
#include "helper.h"
#define green "\x1b[32m"
#define yellow "\x1b[33m"
#define red "\x1b[31m"
#define rst "\x1b[0m"
#define SHLIB_EXT ".so"
int suka=0;
uv_sem_t sem_g;
static uv_async_t async_g;
int gloop_init_success=0;
static GMainContext *sess_watchdog_ctx=NULL;
j_plugin * janus_plugin=NULL;

int j_plugin_push_event(j_plugin*plugin,const char*transaction);
void j_handle_signal(int);

static j_cbs j_handler_plugin={
.push_event=j_plugin_push_event,
};
volatile gint stop=0;

gint stop_signal=0;

//napi_env readEnv=NULL;
//napi_ref readCb;

napi_env msgEnv=NULL;
napi_ref msgCb;
napi_value on_msg_cb(const char*);

void on_clo(uv_handle_t*h){
printf("[sample.c]: on_uv_close handler.\n");
exit(0);
}
void print_to(uv_async_t*h){
printf("[sample.s]: print_to.\n");
if(h->data && (h->data !=NULL)){
printf(green "[sample1.c]: h->data: %p, %s\n" rst,h->data,(char*)h->data);
const char*s=(char*)h->data;	
on_msg_cb(s);
if(!strcmp(s,"exit")){
printf(yellow "[sample1.c]: EXIT!\n" rst);
uv_close((uv_handle_t*)&async_g, on_clo);
	//usleep(24000);
}
}else{
printf(red "[sample1.c]: no message in print_to?\n" rst);
uv_close((uv_handle_t*)&async_g, on_clo);
}


}

void addon_cleanup(){
printf("[sample1.c]: addon_cleanup()\n");
//if(gloop_init_success==0){printf(red "[sample1.c]: gloop_init_success: %d\n" rst,gloop_init_success);return;}else{
//printf(green "[sample1.c]: gloop_init_success: %d\n" rst, gloop_init_success);
//}
//raise(SIGUSR1);
}


//static 
void j_termination_handler(void) {
g_print("[sample1.c]: At exit handler occured.\n");
}

int j_plugin_push_event(j_plugin *plugin, const char*transaction){
if(!plugin){ printf(red "[sample1.c]: plugin is -1\n" rst);return -1;}
printf(green "[sample1.c]: The message came from echo plugin: %s\n" rst,transaction); 
//on_msg_cb(transaction);
const char*t=transaction;
	// TODO place uv_async_send in a queue, sorry to say uv_callback.c library doesn't work without uv loop in other thread
	async_g.data=(void*)t;
	uv_async_send(&async_g);
return 0;
}


void j_handle_signal(int signum) {
	gloop_init_success=0;
	stop_signal = signum;
	switch(g_atomic_int_get(&stop)) {
		case 0:
			g_print("\n[sample1.c]: Stopping gateway, please wait...\n");
			suka=1;
			
			break;
		case 1:
			g_print("[sample1.c]: In a hurry? I'm trying to free resources cleanly, here!\n");
			break;
		default:
			g_print("[sample1.c]: Ok, leaving immediately...\n");
			break;
	}
	
	g_atomic_int_inc(&stop);
	suka=1;
	//g_main_context_wakeup(sess_watchdog_ctx);
	suka=1;
	uv_sem_post(&sem_g);
	if(g_atomic_int_get(&stop) > 2) {
		//g_main_context_wakeup(sess_watchdog_ctx);
		g_print("[sample1.c]: Here must be exit(0).\n");
		exit(0);
	}
		
}
void emexit(){
const char*dexit="exit";
async_g.data=(void*)dexit;
int a=uv_async_send(&async_g);
printf(red "[sample1.c]: a on exit %d\n" rst,a);
if(a !=0) exit(1);
}
const char*dexit="exit";
static void * watcher(void * arg){
signal(SIGINT, j_handle_signal);
signal(SIGUSR1,j_handle_signal);
signal(SIGTERM, j_handle_signal);
//atexit(j_termination_handler);
printf(green "[sample1.c]: Setup Glib.\n" rst);
sess_watchdog_ctx=g_main_context_new();
GMainLoop *watchdog_loop=g_main_loop_new(sess_watchdog_ctx,FALSE);
GError *err=NULL;
GThread *watchdog=g_thread_try_new("sess",&j_sess_watchdog,watchdog_loop,&err);
if(err !=NULL){
printf(red "[sample1.c]: Fatal err trying to start sess watchdog.\n" rst);
emexit();
}
	/*
janus_plugin =(j_plugin*) plugin_create();
//create_p();// for dlopen
if(!janus_plugin) {
printf(red "[sample1.c]: Couldn't use function 'plugin_create'...\n" rst);
emexit();
}
if(!janus_plugin->init || !janus_plugin->destroy ||!janus_plugin->handle_message ) {
printf(red "[sample1.c]: Missing some mandatory methods/callbacks, skipping this plugin...\n" rst);
emexit();
}
if(janus_plugin->init(&j_handler_plugin) < 0) {
printf(red "[sample1.c]: The  plugin could not be initialized.\n" rst);
emexit();
}
	*/
	
	//. dynamically loaded
	
	struct dirent *pluginent = NULL;
	const char *path=NULL;
	DIR *dir=NULL;
	path="/home/globik/kore-mediasoup/addon/emitter5/sample2/plugin";
	
	g_print("Plugins folder: %s\n", path);
	dir = opendir(path);
	if(!dir) {
		g_print("\tCouldn't access plugins folder...\n");
		exit(1);
	}
	
	char pluginpath[1024];
	while((pluginent = readdir(dir))) {
		int len = strlen(pluginent->d_name);
		if (len < 4) {
			continue;
		}
		if (strcasecmp(pluginent->d_name+len-strlen(SHLIB_EXT), SHLIB_EXT)) {
			continue;
		}
		
		g_print("LOADING PLUGIN %s\n",pluginent->d_name);
		
		memset(pluginpath, 0, 1024);
		g_snprintf(pluginpath, 1024, "%s/%s", path, pluginent->d_name);
		void *plugin = dlopen(pluginpath, RTLD_NOW | RTLD_GLOBAL);
		if (!plugin) {
			g_print("\tCouldn't load plugin '%s': %s\n", pluginent->d_name, dlerror());
		} else {
			create_p *create = (create_p*) dlsym(plugin, "plugin_create");
			const char *dlsym_error = dlerror();
			if (dlsym_error) {
				g_print( "\tCouldn't load symbol 'plugin_create': %s\n", dlsym_error);
				continue;
			}
			
	
				janus_plugin = create();
			if(!janus_plugin) {
				g_print("\tCouldn't use function 'plugin_create'...\n");
				continue;
			}
			/* Are all the mandatory methods and callbacks implemented? */
			if(!janus_plugin->init || !janus_plugin->destroy ||!janus_plugin->handle_message ) {
				g_print("\tMissing some mandatory methods/callbacks, skipping this plugin...\n");
				continue;
			}
		
			if(janus_plugin->init(&j_handler_plugin) < 0) {
				g_print( "The  plugin could not be initialized\n");
				dlclose(plugin);
				continue;
			}
			
		}
	}
	
	
	closedir(dir);
	printf("we here 222\n");

while(!g_atomic_int_get(&stop)){
	// it's strange here. Heat cpu? wasted resources?? Busy looping all the time
	// check if sys/signal fd OK for that or semaphor??? coroutine???
	printf("loop_\n");
	
	uv_sem_wait(&sem_g);
	//with semaphore it seems to work as expected, hm.
	// And why Lorenzo doesn't use g_main_context_iteration? I'v tried it - sigint doesn't work at this scenario
	//g_main_context_iteration(sess_watchdog_ctx,TRUE);
	//g_main_context_wakeup(sess_watchdog_ctx);
//usleep(25000);
printf("loop\n");
}
	
	//g_main_context_wakeup(sess_watchdog_ctx);
	

g_print(green "[sample1.c]: Ending watchdog loop.\n" rst);
g_main_loop_quit(watchdog_loop);
g_thread_join(watchdog);
watchdog=NULL;
g_main_loop_unref(watchdog_loop);
g_main_context_unref(sess_watchdog_ctx);
sess_watchdog_ctx=NULL;
if(janus_plugin !=NULL) {janus_plugin->destroy();janus_plugin=NULL;}
g_print("[sample1.c]: ***Bye!***\n");
	//uv_close((uv_handle_t*)&async_g, on_clo);
//emexit();
//const char*dexit="exit";
async_g.data=(void*)"exit";
uv_async_send(&async_g);
	//pthread_exit(NULL);
	//exit(0);
return 0;
}

int write_start(char*s, size_t leni){
printf(green "[sample1.c]: write_start leni: %d\n" rst,leni);
if(janus_plugin==NULL){printf(red "[sample1.c]: janus_plugin is NULL.\n" rst);return -1;}
j_plugin_res *resu=janus_plugin->handle_message(s);
if(resu==NULL){printf(yellow "[sample1.c]: resu is null\n" rst);}
if(resu->type==J_PLUGIN_OK){printf("[sample1.c]: j_plugin_ok\n");}
if(resu->type==J_PLUGIN_OK_WAIT){printf("[sample1.c]: resu->type=> %s\n",resu->text);}
//int res=gw->push_event(&p_m,"Fucker"); in echo.c plugin
j_plugin_res_destroy(resu);
return 0;
}
static int start_watcher(napi_env envi){
static bool watcher_started=false;
	pthread_t thread_id;
	if(watcher_started)return 0;
	int err;
	uv_loop_t * loop=NULL;
	napi_get_uv_event_loop(envi,&loop);
	
	err=uv_sem_init(&sem_g,1);
	if(err<0){
	return -err;
	}
	
	
	err=uv_async_init(loop, &async_g, print_to);
	if(err<0) {
	uv_sem_destroy(&sem_g);	
	return -err;}
	err=pthread_create(&thread_id,0,watcher,0);
	if(err !=0){
	uv_sem_destroy(&sem_g);
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
int err=start_watcher(env);
if(err==0){
printf(yellow "[%s]: Thread with a glib loop created! %d\n" rst,__FILE__, err);
gloop_init_success=1;
}else{
printf(red "[sample1.c]: Failed to create a thread with a glib loop! %d\n" rst, err);
}
	
napi_value argv[1];

const char * str = "created!";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){printf(red "[sample1.c]: Call_func p_create [result] is NOT OK!\n" rst);}
return NULL;
}

napi_value p_send(napi_env env, napi_callback_info info)
{
if(gloop_init_success==0){printf(red "[sample1.c]: gloop_init_success: %d\n" rst,gloop_init_success);return NULL;}
napi_status k;
size_t argc = 2; // input buffer and callback
napi_value args[2]; // callback
napi_get_cb_info(env, info, &argc, args, NULL, NULL);

//napi_handle_scope scope;
//napi_open_handle_scope(env,&scope);
//const unsigned char*input;
//raise(SIGUSR1);
if(g_atomic_int_get(&stop) > 0){printf(red "[sample1.c]: atomic stop > 0, stop write.\n" rst); return NULL;}
char*input;char*muka;
size_t len;
bool is_buf;
k=napi_is_buffer(env,args[0],&is_buf);
if(k !=napi_ok){printf( red "status buf failed.\n" rst);return NULL;}
if(is_buf){
//printf("IS BUFFER!\n");
k=napi_get_buffer_info(env,args[0],(void**)(&input),&len);
if(k !=napi_ok){
printf(red "failed to get buffer info input.\n" rst);
return NULL;
}
//printf("length: %d\n",len);
input[len]=0;
muka=input;
//printf("INPUT: %s\n",muka);
}else{
printf(red "IS NOT A BUFFER\n" rst);
return NULL;
}


if(gloop_init_success==0){printf(red "[sample1.c]: gloop thread is NOT initialised.\n" rst);return NULL;}
napi_value argv[2];// for cb args: err, data

//if(is_read){
	
//int kak=uv_loop_alive(loop);
//printf("IS ALIVE_#############: %d\n",kak);
int mu=write_start(muka,len);
printf("[sample1.c]: write start is OK? %d\n", mu);
const char * str = "write_result";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, &argv[1]);
napi_get_null(env,&argv[0]);
//}else{
//const char * str = "what_the_fuck";
//size_t str_len = strlen(str);
//napi_create_string_utf8(env, str, str_len, &argv[0]);
//napi_get_null(env,&argv[1]);
//}

napi_value global;
napi_get_global(env, &global);
napi_value cb = args[1];//args[0] is an input buffer, args[1] is output -> callback(err,data)=>err is &argv[0], data is &argv[1]

k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){
printf(red "call_func in p_send is NOT ok!\n" rst);
}
//k=napi_close_handle_scope(env,scope);
//if(k==napi_ok){printf("close_scope is ok\n");}else{printf("close_scope is not ok\n");}
return NULL;
}

napi_value p_close(napi_env env, napi_callback_info info)
{
//if(gloop_init_success==0)return NULL;
raise(SIGUSR1);
	//uv_async_send(&async_g);
napi_status k;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);

//addon_cleanup();

if(msgEnv !=NULL){
//printf("msgEnv is NOT NULL.\n");
k=napi_delete_reference(msgEnv, msgCb);
if(k==napi_ok){ printf("[sample1.c]: del_ref msgCb is OK.\n");}else{printf(red "[sample1.c]: del_ref msgCb is NOT OK.\n" rst);}
msgEnv=NULL;	
}
//	raise(SIGUSR1);
	//uv_close((uv_handle_t*)&async_g, on_clo);
//	usleep(1);
//usleep(1000);
//return NULL;
napi_value argv[1];

const char * str = "close_result";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){
printf(red "call_func in p_close[result] is NOT OK!\n" rst);
return NULL;
}
return NULL;
}

napi_value on_msg_cb(const char*msg_str){
printf(yellow "[sample1.c]: on_msg_cb\n" rst);
napi_status k;
if(msgEnv == NULL){printf(red "[sample1.c]: msgEnv is NULL.\n" rst); return NULL;}
napi_value callback;
napi_handle_scope scope;
napi_open_handle_scope(msgEnv,&scope);
napi_value argv[1];
const char * str = msg_str;//"now_readable";
size_t str_len = strlen(str);
k=napi_create_string_utf8(msgEnv, str, str_len, argv);
if(k !=napi_ok){printf(red "[sample1.c]: cr_str1 in on_msg_cb is NOT ok!\n" rst);
			//return NULL;
			   }
k=napi_get_reference_value(msgEnv, msgCb, &callback);
if(k !=napi_ok){printf(red "[sample1.c]: get_ref in on_msg_cb is NOT ok!\n" rst);
			//return NULL;
			   }
napi_value global;
k=napi_get_global(msgEnv, &global);
if(k !=napi_ok){printf(red "[sample1.c]: get_glob in on_msg_cb is NOT ok!\n" rst);
				//return NULL;
			   }
k=napi_call_function(msgEnv, global, callback, 2, argv, NULL);
if(k !=napi_ok){printf(red "{sample1.c]: call_func in on_msg_cb is NOT ok!\n" rst);
//return NULL;
}
k=napi_close_handle_scope(msgEnv,scope);
if(k !=napi_ok){printf(red "[sample1.c]: close_scope is not ok\n" rst);}
return NULL;
}

napi_value on_msg(napi_env env,napi_callback_info info){
//printf("****ONONON MSG MSG***\n");
if(gloop_init_success==0){printf(red "[sample1.c]: on_msg gloop_init_success: %d\n" rst,gloop_init_success);return NULL;}
napi_status k;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);

if(msgEnv==NULL){
msgEnv=env;
}
napi_value argv[1];
k=napi_create_reference(env, args[0], 2, &msgCb);
if(k !=napi_ok){printf(red "[sample1.c]: Create reference on_msg is NOT ok.\n" rst);msgEnv=NULL;return NULL;}
const char * str = "on_msg_prepare";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){
printf(red "[sample1.c]: call_func on_msg is NOT ok!\n" rst);
msgEnv=NULL;
}
return NULL;
}
void hani(){
printf("hani\n");
	//uv_close((uv_handle_t*)&async_g, on_clo);
	//usleep(1000000);
//addon_cleanup();
	//raise(SIGUSR1);
	if(msgEnv !=NULL){
//printf("msgEnv is NOT NULL.\n");
napi_status k=napi_delete_reference(msgEnv, msgCb);
if(k==napi_ok){ printf("[sample1.c]: del_ref msgCb is OK.\n");}else{printf(red "[sample1.c]: del_ref msgCb is NOT OK.\n" rst);}
msgEnv=NULL;	
}
	uv_sem_destroy(&sem_g);	
}

napi_value Init(napi_env env, napi_value exports)
{
atexit(hani);
	napi_status status;
	napi_value fn, fn1,fn2,fn3;//fn4;
	status=napi_create_function(env,NULL,0,p_create,NULL,&fn);
	if(status !=napi_ok){printf(red "create func p_create failed.\n" rst);return NULL;}
	status=napi_set_named_property(env,exports,"p_create",fn);
	if(status !=napi_ok){printf(red "set prop p_create failed.\n" rst);return NULL;}
	
	status=napi_create_function(env,NULL,0,p_send,NULL,&fn1);
	if(status !=napi_ok){printf(red "create func p_send failed.\n" rst);return NULL;}
	status=napi_set_named_property(env,exports,"p_send",fn1);
	if(status !=napi_ok){printf(red "set prop p_send failed.\n" rst);return NULL;}
	
	status=napi_create_function(env,NULL,0,p_close,NULL,&fn2);
	if(status !=napi_ok){printf(red "create func p_close failed.\n" rst);return NULL;}
	status=napi_set_named_property(env,exports,"p_close",fn2);
	if(status !=napi_ok){printf(red "set prop p_close failed.\n" rst);return NULL;}
	
	status=napi_create_function(env,NULL,0, on_msg,NULL,&fn3);
	if(status !=napi_ok){printf(red "create func on_msg failed.\n" rst);return NULL;}
	status=napi_set_named_property(env,exports,"on_msg",fn3);
	if(status !=napi_ok){printf(red "set prop on_msg failed.\n" rst);return NULL;}
	return exports;
}
NAPI_MODULE(addon,Init)