#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>//exit
#include "helper.h"

static gboolean j_check_sess(gpointer);

/*
void j_handle_signal(int signum) {
	stop_signal = signum;
	switch(g_atomic_int_get(&stop)) {
		case 0:
			g_print("Stopping gateway, please wait...\n");
			break;
		case 1:
			g_print("In a hurry? I'm trying to free resources cleanly, here!\n");
			break;
		default:
			g_print("Ok, leaving immediately...\n");
			break;
	}
	g_atomic_int_inc(&stop);
	if(g_atomic_int_get(&stop) > 2) {
		g_print("here must be exit(1)\n");
		exit(1);
	}
		
}
*/
static gboolean j_check_sess(gpointer user_data){
	printf("tick-tack\n");
	//g_main_context_wakeup(NULL);
return G_SOURCE_CONTINUE;
}

gpointer j_sess_watchdog(gpointer user_data){
GMainLoop *loop=(GMainLoop *)user_data;
	GMainContext *watchdog_ctx=g_main_loop_get_context(loop);
	GSource *timeout_source=g_timeout_source_new_seconds(2);
	g_source_set_callback(timeout_source,j_check_sess,watchdog_ctx,NULL);
	g_source_attach(timeout_source,watchdog_ctx);
	g_source_unref(timeout_source);
	//g_main_context_wakeup(watchdog_ctx);
	printf("[helper.c]: Session watchdog started!\n");
	g_main_loop_run(loop);
	//g_main_context_wakeup(watchdog_ctx);
	return NULL;
}
