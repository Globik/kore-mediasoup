#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // usleep
//#include <dlfcn.h>
//#include <dirent.h>
//#include <net/if.h>
//#include <netdb.h>
//#include <sys/resource.h>
//#include <sys/stat.h>
//#include <signal.h>
//#include <limits.h>
//include <glib.h>
#include <pthread.h>
#include "plugin.h"
#include "helper.h"
#define green "\x1b[32m"
#define yellow "\x1b[33m"
#define red "\x1b[31m"
#define rst "\x1b[0m"

static GMainContext *sess_watchdog_ctx=NULL;
j_plugin * janus_plugin=NULL;

int j_plugin_push_event(j_plugin*plugin,const char*transaction);

static j_cbs j_handler_plugin={
.push_event=j_plugin_push_event,
};
volatile gint stop=0;

gint stop_signal=0;
static void j_termination_handler(void) {g_print("at exit handler occured.\n");}

int j_plugin_push_event(j_plugin *plugin,const char*transaction){
if(!plugin){ printf(red "plugin is -1\n" rst);return -1;}
printf(green "TRANSACTION: %s\n" rst,transaction); 
return 0;
}

int main(){
signal(SIGINT, j_handle_signal);
signal(SIGTERM, j_handle_signal);
atexit(j_termination_handler);
g_print(" Setup Glib \n");
sess_watchdog_ctx=g_main_context_new();
GMainLoop *watchdog_loop=g_main_loop_new(sess_watchdog_ctx,FALSE);
GError *err=NULL;
GThread *watchdog=g_thread_try_new("sess",&j_sess_watchdog,watchdog_loop,&err);
if(err !=NULL){
printf("fatal err trying to start sess watchdog\n");
exit(1);
}
	
janus_plugin =(j_plugin*) plugin_create();
//create_p();// for dlopen
if(!janus_plugin) {
				g_print("\tCouldn't use function 'plugin_create'...\n");
			
			}if(!janus_plugin->init || !janus_plugin->destroy ||!janus_plugin->handle_message ) {
				g_print("\tMissing some mandatory methods/callbacks, skipping this plugin...\n");
			
			}
if(janus_plugin->init(&j_handler_plugin) < 0) {
g_print( "The  plugin could not be initialized\n");
}
	
j_plugin_res *resu=janus_plugin->handle_message("dudka_DUDKA");
if(resu==NULL){printf(yellow "resu is null\n" rst);}
if(resu->type==J_PLUGIN_OK){printf("j_plugin_ok\n");}
if(resu->type==J_PLUGIN_OK_WAIT){printf("J_PLUGIN_OK_WAIT: %s\n",resu->text);}
//int res=gw->push_event(&p_m,"Fucker"); in echo.c plugin
j_plugin_res_destroy(resu);
	
while(!g_atomic_int_get(&stop)){
usleep(250000);
}
	
g_print("ending watchdog loop\n");
g_main_loop_quit(watchdog_loop);
g_thread_join(watchdog);
watchdog=NULL;
g_main_loop_unref(watchdog_loop);
g_main_context_unref(sess_watchdog_ctx);
sess_watchdog_ctx=NULL;
if(janus_plugin !=NULL) {janus_plugin->destroy();janus_plugin=NULL;}
g_print("Bye!\n");
return 0;
}