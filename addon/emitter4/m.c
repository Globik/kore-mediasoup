#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/eventfd.h>
#include <stdint.h>

#include <sys/un.h>
#include <sys/types.h>
#include <node_api.h>


#include <uv.h>
#define socket_name "/home/globik/fuck"
static uv_poll_t stdin_watcher;
//static uv_poll_t sockin_watcher,sockout_watcher,disconnect_watcher;
//static uv_os_sock_t data_socket;
int uv_poll_init_success=0;
int fucker=0;
int ev_fd;
char*super_str;
uint64_t ev_u;
//static char log_buf[4096];
//static size_t log_buf_pos=0;
static void on_eventfd_read(uv_poll_t*,int,int);
//static void on_sock_read(uv_poll_t*,int,int);
//static void on_sock_write(uv_poll_t*,int,int);
//static void on_disconnect(uv_poll_t*watcher,int status,int revents);
static void on_clo(uv_handle_t*);
static void at_pexit(void);
static int evfd_init(void);
static int uvpoll_init(napi_env,int);
static void uvpoll_cleanup(void);
static void evfd_send(int);
static void evfd_send(int fd){
ev_u=1;
ssize_t slen=write(fd, &ev_u, sizeof(uint64_t));
if(slen !=sizeof(uint64_t)){
printf("!slen\n");
uvpoll_cleanup();
}else{
printf("slen is ok\n");
}
}
static void uvpoll_cleanup(){
printf("uvpoll_cleanup() occured.\n");
if(uv_poll_init_success==0){ printf("sucess init: %d\n",uv_poll_init_success);return;}else{
printf("sucess init: %d\n",uv_poll_init_success);
}
uv_poll_stop(&stdin_watcher);
uv_close((uv_handle_t*)&stdin_watcher,on_clo);
//usleep(5);
if(ev_fd) close(ev_fd);
uv_poll_init_success=0;
} 

static int evfd_read_start(napi_env);

static void on_clo(uv_handle_t*h){
printf("on_clo occured.\n");
printf("handle: %p, h->data: %p\n",h,h->data);
}

static int evfd_init(){
ev_fd=eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
if(ev_fd==-1){
//errno("ev_fd failed: ");
printf("ev_fd is -1\n");
//exit(EXIT_FAILURE);
return -1;
}else{
printf("ev_fd is: %d\n",ev_fd);
return ev_fd;
}
}
static int uvpoll_init(napi_env env, int fd){
if(!fd) {printf("fd is undefined\n");return -1;}
	
	uv_loop_t *loop=NULL;
	napi_status status=napi_get_uv_event_loop(env,&loop);
	if(status==napi_ok){
		printf("loop is ok\n");
	}else{
		printf("loop is NOT ok\n");
		//return NULL;
	}
	
	
	
	
int s=uv_poll_init(loop, &stdin_watcher, fd);
if(0 !=s){
	//errno("poll init failed: ");
printf("poll init failed\n");return -1;}
uv_poll_init_success=1;
return 0;
}

static int evfd_read_start(napi_env env){
int f_d=evfd_init();
if(f_d==-1){
printf("evfd_init failed\n");
return -1;
}else{
int poll_status=uvpoll_init(env,f_d);
	if(poll_status==-1){
	close(f_d);
	return -1;
	}
printf("STARTING POLL\n");
uv_poll_start(&stdin_watcher, UV_READABLE, on_eventfd_read);
return 0;
}
}

static void on_eventfd_read(uv_poll_t*watcher,int status,int revents){
	fucker++;
	printf("fucker: %d",fucker);
	printf("revents: %d, status: %d\n",revents,status);
	if(fucker==10){
		/*
	uv_poll_stop(&stdin_watcher);
	uv_close((uv_handle_t*)&stdin_watcher,on_clo);
	close(ev_fd);
	*/
		uvpoll_cleanup();
		return;
	}
	if(revents & UV_READABLE){
	//sockin_watcher.data="what the fuck?";
	printf("REVENTS: %d STATUS: %d\n",revents,status);
	ssize_t mu=read(evfd,&u,sizeof(uint64_t));
	if(mu !=sizeof(uint64_t)){printf("ev read not size64\n");}else{
	printf("return ev read %lld\n",u);
	uv_poll_start(&sockin_watcher, UV_WRITABLE | UV_DISCONNECT, on_sock_write);
	
	}
}

napi_value p_init(napi_env env, napi_callback_info info)
{
//napi_status k;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);
if(argc == 1){
printf("OK in a number of argc. A single argument as expected: %d\n", argc);
}else{
printf("argc is %d\n", argc);
}
napi_valuetype val0;
napi_typeof(env, args[0], &val0);
if(val0 == napi_function){
printf("OK, args[0] is a function.\n");
}else{
printf("args[0] is not a function.\n");
}
napi_valuetype val1;
napi_typeof(env, args[1], &val1);
if(val1 == napi_undefined){
printf("args[1] is undefined.\n");
}else{
printf("Additional args[1] should be undefined.\n");
}

napi_value argv[1];

	
	int a=evfd_read_start(env);
	printf("EVFD_READ_START(): %d\n",a);
	
const char * str = "start_result";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
napi_status status = napi_call_function(env, global, cb, 2, argv, NULL);
if(status == napi_ok){
printf("napi_status is OK! Event fired!\n");
}else{
printf("napi_status is NOT OK!\n");
return NULL;
}
return NULL;
}

napi_value p_close(napi_env env, napi_callback_info info)
{
//napi_status k;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);
if(argc == 1){
printf("OK in a number of argc. A single argument as expected: %d\n", argc);
}else{
printf("argc is %d\n", argc);
}
napi_valuetype val0;
napi_typeof(env, args[0], &val0);
if(val0 == napi_function){
printf("OK, args[0] is a function.\n");
}else{
printf("args[0] is not a function.\n");
}
napi_valuetype val1;
napi_typeof(env, args[1], &val1);
if(val1 == napi_undefined){
printf("args[1] is undefined.\n");
}else{
printf("Additional args[1] should be undefined.\n");
}

napi_value argv[1];

const char * str = "close_result";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
napi_status status = napi_call_function(env, global, cb, 2, argv, NULL);
if(status == napi_ok){
printf("napi_status is OK! Event fired!\n");
}else{
printf("napi_status is NOT OK!\n");
return NULL;
}
return NULL;
}


napi_value p_send_ev_fd(napi_env env, napi_callback_info info)
{
//napi_status k;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);
if(argc == 1){
printf("OK in a number of argc. A single argument as expected: %d\n", argc);
}else{
printf("argc is %d\n", argc);
}
napi_valuetype val0;
napi_typeof(env, args[0], &val0);
if(val0 == napi_function){
printf("OK, args[0] is a function.\n");
}else{
printf("args[0] is not a function.\n");
}
	

	
napi_valuetype val1;
napi_typeof(env, args[1], &val1);
if(val1 == napi_undefined){
printf("args[1] is undefined.\n");
}else{
printf("Additional args[1] should be undefined.\n");
}
evfd_send(ev_fd);
napi_value argv[1];

const char * str = "eventfd_result";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
napi_status status = napi_call_function(env, global, cb, 2, argv, NULL);
if(status == napi_ok){
printf("napi_status is OK! Event fired!\n");
}else{
printf("napi_status is NOT OK!\n");
return NULL;
}
return NULL;
}

static void at_pexit(){
printf("at_exit cb occured.\n");
uvpoll_cleanup();
}

napi_value Init(napi_env env, napi_value exports)
{
atexit(at_pexit);
napi_property_descriptor desc[3] = {
	{"p_init",0, p_init, 0, 0, 0, napi_default, 0},
	{"p_close",0,p_close, 0, 0, 0, napi_default, 0},
	{"p_send_ev_fd",0,p_send_ev_fd,0,0,0,napi_default,0}
};
napi_define_properties(env, exports, sizeof(desc)/sizeof(*desc), desc);
return exports;
}
NAPI_MODULE(addon,Init)
