
#include <node_api.h>
#include <string.h>
#include <stdio.h>//printf
#include <stdlib.h>
#include <unistd.h> // sleep
#include <ee.h> // event emitter in C https://github.com/thlorenz/ee.c

#include <sys/socket.h>
#include <sys/un.h>

#include <signal.h>

#include <sys/select.h>
#include <errno.h>

#include <fcntl.h>
#include <time.h>
#define socket_name "/home/globik/fuck"
#define buffer_size 512


#include <uv.h>
const char*event_hello="hello";
const char*event_down="down";
const char*event_dummy="dummy";
uv_mutex_t mutex;
int debug=0;
sigset_t mask;
sigset_t orig_mask;
struct sigaction act;
typedef  void(*on_suka)(int d);
static volatile int exit_req=0;
static volatile int commit=1;
/*
static void hdl(int sig){
exit_req=1;
}
*/

struct timeval tv;
//tv->tv_sec=0;
//=6;
	//tv.tv_usec=0;

void signal_handler(uv_signal_t*req,int signum){
printf("signal received.\n");
	exit_req=1;
	uv_signal_stop(req);
}
void print_to(uv_async_t*);
void on_down(void*);
napi_value fucker(const char*);
void HANI(int f){
printf("HANI\n");
//FD_SET(data_socket, &write_fds);
	return;
}
// cd kore-mediasoup/addon/emitter1 
void suka(int bc){
printf("SUKA!\n");
//sleep(10);
printf("AFTER SUKA\n");
}
fd_set write_fds;
int data_socket=0;

int a=0;
int can_write=0;


typedef struct{
napi_ref _callback;
napi_async_work _request;
}carrier;

napi_env shenv=NULL;
napi_env menv=NULL;
ee_t*ee=NULL;
napi_ref dcb;

uv_async_t async, vasync;

void print(uv_async_t*handle){
	printf("***PRINT***: %s\n",(char*)handle->data);
	//if(ee !=NULL){printf("ee is NOT NULL!!!\n"); ee_emit(ee,event_hello,(char*)handle->data);}
	char*li=(char*)handle->data;
	if(!strcmp(li,"message")){
	if(ee !=NULL)ee_emit(ee,event_down,"FOR_MESSAGE");
	}else{
	if(ee !=NULL){printf("ee is NOT NULL!!!\n"); ee_emit(ee,event_hello,(char*)handle->data);}
	}
	//napi_status k;
	//fucker();
	//fucker();
	//fucker();
	//printf("AAAAAAAAAAAAAAAAAAA: %d\n",a);
	}

void dow(int s, on_suka suk){
char buf[512];int ret;
	
	
//async.data=(void*)"***FOR_MESSAGE_ASYNC***";
//int ab=uv_async_send(&async);
//printf("status async: %d\n",ab);

if(commit==0){
strcpy(buf,"Hallo world!");
int leni=strlen(buf)+1;
ret=send(s,buf, leni, 0);
if(ret==-1){
perror("write2");
close(s);
return;
exit(EXIT_FAILURE);
}
printf("leni: %d, ret: %d\n",leni,ret);
can_write=1;
commit=1;
}
}
// cd kore-mediasoup/addon/emitter1
void on_dummy(void*arg){
	printf("ON_DUMMY occured => %s\n",(char*)arg);
const char*f="ON_DUMMY_EVENT";
	uv_mutex_lock(&mutex);
//fucker(f);
	//uv_mutex_unlock(&mutex);
	
	async.data=(void*)arg;
int ab=uv_async_send(&async);
printf("status async_dummy: %d\n",ab);
	uv_mutex_unlock(&mutex);
}
void on_hello(void*arg){
const char*s=(const char*)arg;
printf("invoked `on_hello` event with: %s\n",s);
	
fucker(s);
}
void on_down(void*a){
printf("ON DOWN OCCURED: %s.\n",(char*)a);
	printf("pre_commit: %d\n",commit);
commit=0;
	printf("post_commit: %d\n",commit);
	/*
exit_req=1;
	if(data_socket !=0){
	printf("DATA_SOCKET IS NOT 0, closing in on_down\n");
		close(data_socket);
		data_socket=0;
	}else{printf("data socket is 0\n in on_down\n");}
	tv.tv_sec=0;
	raise(SIGUSR1);
	return;
	*/
	//can_write=0;
	//FD_SET(data_socket, &write_fds);
	//break;
}
napi_value fucker(const char*st){
a++;
napi_status k;
printf("fucker\n");
if(shenv == NULL){printf("NULLLLLL\n"); return NULL;}
napi_value cbu;
napi_handle_scope scope;
napi_open_handle_scope(shenv,&scope);
napi_value argv[1];
const char * str = st;//"start*****************************************";
size_t str_len = strlen(str);
printf("suka\n");
k=napi_create_string_utf8(shenv, str, str_len, argv);
if(k==napi_ok){printf("cr_str1 is ok\n");}else{printf("cr_str1 is not ok\n");}
k=napi_get_reference_value(shenv, dcb, &cbu);
if(k==napi_ok)printf("get_ref is ok\n");
napi_value global;
k=napi_get_global(shenv,&global);
if(k==napi_ok){printf("get_glob is ok\n");}else{printf("get_glob is not ok\n");}
k=napi_call_function(shenv, global, cbu, 2, argv,NULL);
if(k==napi_ok){printf("call_func is ok\n");}else{printf("call_func is not ok\n");return NULL;}
k=napi_close_handle_scope(shenv,scope);
if(k==napi_ok){printf("close_scope is ok\n");}else{printf("close_scope is not ok\n");}
return NULL;
}

napi_value callEmit(napi_env env, napi_callback_info info)
{
napi_status k;
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
if(shenv==NULL){
printf("SHENV is NULL\n");
shenv=env;
}
napi_value argv[1];
k=napi_create_reference(env, args[0], 10, &dcb);
if(k==napi_ok){printf("create reference is ok\n");}else{printf("create reference is not ok\n");}
const char * str = "start";
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

void Execute(napi_env env, void*data){
fprintf(stderr,"Entering Execute()\n");
if(data==NULL){printf("data is null\n");return;}
carrier*c=(carrier*)data;
if(!c){printf("!c\n");return;}
//if(ee !=NULL)ee_on(ee,event_hello,on_hello);
//async.data=(void*)"L";
//int ab=uv_async_send(&async);
//printf("status of uv_async_send: %d\n",ab);
	/*
	uv_loop_t *loop=NULL;//uv_default_loop();
	
	napi_status status=napi_get_uv_event_loop(env,&loop);
	if(status==napi_ok){
		printf("loop is ok in exec\n");
	}else{
		printf("loop is NOT ok in exec\n");
		return;
	}
	*/
//int abi=uv_async_init(loop, &vasync, print_to);
//	printf("uv_async_init vasync abi : %d\n", abi);
	
//struct timeval tv;
tv.tv_sec=20;
tv.tv_usec=0;
struct sockaddr_un addr;
int ret;
int br=0;
char buffer[buffer_size];
data_socket=socket(AF_UNIX,SOCK_SEQPACKET | O_NONBLOCK,0);
fprintf(stderr,"DATA_SOCKET: %d\n",data_socket);
if(data_socket==-1){
perror("socket");
fprintf(stderr,"DATA SOCKET IS -1 !!\n");
//exit(EXIT_FAILURE);

return;
//async.data=(void*)"SERVER IS DOWN!!!";
	//ab=uv_async_send(&async);
	//printf("status async: %d\n",ab);
}
printf("AFTER DATA SOCKET\n");
	
memset(&addr,0,sizeof(struct sockaddr_un));
addr.sun_family=AF_UNIX;
strncpy(addr.sun_path,socket_name,sizeof(addr.sun_path)-1);
ret=connect(data_socket,(const struct sockaddr*)&addr,sizeof(struct sockaddr_un));
if(ret==-1){
fprintf(stderr,"the server is down\n");
close(data_socket);
//async.data=(void*)"SERVER IS DOWN!!!";
//ab=uv_async_send(&async);
//printf("status async: %d\n",ab);
//return;
exit_req=1;

//exit(EXIT_FAILURE);
}
	/*
	while(1){
		br++;
	printf("WHILEEEEEEEEEE\n");
		if(br==100){printf("br is 100, break\n");break;}
	}
	*/
	
	
fd_set read_fds;
//fd_set except_fds;
//signal(SIGUSR1,HANI);
//if(ee !=NULL)ee_on(ee,event_down,on_down);
while(!exit_req){
br++;
if(debug)fprintf(stderr, "BR_BR: %d\n",br);
FD_ZERO(&read_fds);
FD_SET(data_socket, &read_fds);
FD_ZERO(&write_fds);
if (can_write == 0){ 
//printf("there is smth to send, set up write_fd for server socket!!!\n");
FD_SET(data_socket, &write_fds);
}
if(debug)fprintf(stderr, "BEFORE ACTIVITY\n");
//raise(SIGUSR1);
if(br==2000){
fprintf(stderr,"HAHA! br is : %d\n",br);
close(data_socket);
data_socket=0;
exit_req=1;
break;
}
	// cd kore-mediasoup/addon/emitter1
	//signal(SIGUSR1,HANI);
//if(br==3){fprintf(stderr,"br=3\n");exit_req=1;close(data_socket);data_socket=0;break;}
	//if(ee !=NULL)ee_on(ee,event_down,on_down);
if(br==10){
	if(ee !=NULL){
		//uv_mutex_lock(&mutex);
		ee_emit(ee,event_dummy,"dummable_1");
		//uv_mutex_unlock(&mutex);
		ee_emit(ee,event_dummy,"dummable_2");
	ee_emit(ee,event_dummy,"dummable_3");
	}
fprintf(stderr,"br=%d\n",br);
	/*
async.data=(void*)"message";
int ab=uv_async_send(&async);
printf("status async_1: %d\n",ab);
*/
	
		//close(data_socket);
		//data_socket=0;
		//tv.tv_sec=0;
		//return;
	}
	/*
if(br==25){
fprintf(stderr,"br=%d\n",br);
async.data=(void*)"IN_MESSAGE_2!!!";
int ab1=uv_async_send(&async);
printf("status async_2: %d\n",ab1);
}
*/
int activity = select(data_socket + 1, &read_fds, &write_fds, NULL, &tv/*,SIGINT*/);
if(debug)fprintf(stderr, "ACTIVITY: %d\n",activity);
if(activity==2){fprintf(stderr,"activity 2\n");close(data_socket);data_socket=0;exit_req=1;break;}
switch (activity) {
case -1:
perror("select()");
printf("%d\n",errno);
close(data_socket);
		data_socket=0;
		exit_req=1;
	// cd kore-mediasoup/addon/emitter1	
		break;
//shutdown_properly(EXIT_FAILURE);
case 0:
printf("EXIT REQ??? select() returns 0.\n");
close(data_socket);
exit_req=1;
break;
//continue;		
//return;
//shutdown_properly(EXIT_FAILURE);

default:
if(exit_req){close(data_socket);break;}
if (FD_ISSET(data_socket, &read_fds)) {
if(debug)fprintf(stderr,"SERVER READ_FDS!!!!!!!!!!!\n");
ret=read(data_socket,buffer,buffer_size);
if(ret==-1){
perror("read");
fprintf(stderr,"read error occured\n");
close(data_socket);
	data_socket=0;
break;
//exit(EXIT_FAILURE);
}
buffer[ret-1]=0;
fprintf(stderr,"result => %s\n",buffer);
fprintf(stderr,"result->br => %d\n",br);
async.data=(void*)buffer;
int ab3=uv_async_send(&async);
printf("status async_ab3: %d\n",ab3);
/*
if(ee !=NULL){printf("ee is NOT NULL!!!\n");
ee_emit(ee,event_hello,"room create!\n");
}
*/
can_write=0;
}

if (FD_ISSET(data_socket, &write_fds)) {
if(debug)fprintf(stderr,"SERVER WRITE_FDS!!!!!!!!!!!!!!!!\n");
dow(data_socket,suka);
}
}
if(debug)fprintf(stderr,"end of while\n");
}
fprintf(stderr,"end of execute()\n");
}
/*
void print(uv_async_t*handle){
	printf("print***print: %s\n",(char*)handle->data);
	if(ee !=NULL){printf("ee is NOT NULL!!!\n"); ee_emit(ee,event_hello,"room create!\n");}
	ee_emit(ee,event_down,"FOR_MESSAGE");
	//napi_status k;
	//fucker();
	//fucker();
	//fucker();
	//printf("AAAAAAAAAAAAAAAAAAA: %d\n",a);
	}
	*/
void print_to(uv_async_t*handle){
	printf("*************************************************\n");
	printf("print_to() occured. : %s\n",(char*)handle->data);
	printf("*************************************************\n");
	printf("*************************************************\n");
	printf("*************************************************\n");
}


void Complete(napi_env env,napi_status status,void*data){
	printf("Entering Complete()\n");
    carrier*c=(carrier*)data;
	if(status !=napi_ok){printf("status is NOT OK.\n");return;}else{printf("status is ok\n");}
	napi_value argv[2];
	napi_get_null(env,&argv[0]);
	napi_value callbac;
	napi_status k=napi_get_reference_value(env,c->_callback, &callbac);
	if(k==napi_ok)printf("get_ref is ok\n");
	napi_value globali;
	k=napi_get_global(env,&globali);
	if(k==napi_ok)printf("get_glob is ok\n");
	
	if(status==napi_ok)printf("status is ok\n");
	const char * str = "start_up";
	size_t str_len = strlen(str);
	napi_create_string_utf8(env, str, str_len, &argv[1]);
	
	k=napi_call_function(env, globali, callbac, 2, argv, NULL);
	if(k==napi_ok){printf("call_func is ok\n");}else{printf("call_func is not ok\n");}
	
	
	printf("deleting reference\n");
	k=napi_delete_reference(env,c->_callback);
	if(k==napi_ok){printf("del_ref is ok\n");}else{printf("del_ref is not ok\n");}
	k=napi_delete_async_work(env,c->_request);
	if(k==napi_ok){printf("del_work is ok\n");}else{printf("del_work is not ok\n");}
	free(c);
}

napi_value create_async(napi_env env, napi_callback_info info){
size_t argc=3;
	napi_value argv[3], resource_name, _this;
	void*data;
	carrier*c=malloc(sizeof(carrier));
	if(c==NULL)return NULL;
	menv = env;
	uv_loop_t *loop=NULL;
	napi_status status=napi_get_uv_event_loop(env,&loop);
	if(status==napi_ok){
		printf("loop is ok\n");
	}else{
		printf("loop is NOT ok\n");
		return NULL;
	}
	

	napi_get_cb_info(env,info, &argc,argv, &_this, &data);
	napi_create_reference(env, argv[2], 1, &c->_callback);
	napi_create_string_utf8(env,"testi",NAPI_AUTO_LENGTH,&resource_name);
	//uv_signal_t sig;
	//uv_signal_init(loop,&sig);
	//uv_signal_start(&sig,signal_handler,SIGINT);
    int ab=uv_async_init(loop, &async, print);
	printf("uv_async_init: %d\n", ab);
	napi_create_async_work(env, argv[1], resource_name, Execute, Complete, c, &c->_request);
	napi_queue_async_work(env, c->_request);
	//sleep(1000);
	if(ee !=NULL){
		ee_on(ee,event_down,on_down);
		ee_on(ee,event_hello,on_hello);
		ee_on(ee,event_dummy,on_dummy);
	}
	
	return NULL;
}
void han(void){
	// don't forget into the node.js script to add the process.on('SIGINT',()=>process.exit(0))
printf("ON_EXIT occured!!!\n");
	exit_req=1;
//ee_emit(ee,event_down,"exit");
//	usleep(1000);
if(ee !=NULL){
ee_remove_listener(ee,event_hello,on_hello);
	ee_remove_listener(ee,event_down,on_down);
	ee_remove_listener(ee,event_dummy,on_dummy);
ee_destroy(ee);
ee=NULL;
printf("ee must be null.\n");
}
printf("closing data socket in han()\n");
if(data_socket !=0){printf("data socket !=0\n");
					close(data_socket);
				   }else{printf("data socket is %d\n",data_socket);}
	
	//carrier*c;
	if(menv !=NULL){
		printf("menv is not NULL\n");
		//napi_status h=napi_cancel_async_work(menv, c->_request);
		//if(h==napi_ok){printf("cancel OK\n");}else{printf("cancel is NOT IK\n");}
		
menv=NULL;
//vasync.data=(void*)"While Loop CLOOOOOSING?";
//int ab=uv_async_send(&vasync);
//printf("status async: %d\n",ab);
	}
	
napi_status k=napi_delete_reference(shenv, dcb);
if(k==napi_ok){ printf("del_ref is ok\n");}else{printf("del_ref is not ok\n");}
//usleep(10000000);
uv_close((uv_handle_t*)&async,NULL);
	uv_mutex_destroy(&mutex);
//uv_close((uv_handle_t*)&vasync,NULL);
}

void cleanup(void*arg){}
int secret=7;

napi_value Init(napi_env env, napi_value exports)
{
// not available yet in node.js v 9.0
	//napi_add_env_cleanup_hook(env,cleanup,&secret,8);
	ee=ee_new();
	if(ee==NULL){printf("ee is NULL\n");}else{printf("ee is NOT NULL\n");}
	int r=uv_mutex_init(&mutex);
	if(r==0){printf("mutex ok\n");}else{printf("mutext not ok\n");}
	atexit(han);
	/*
	memset(&act,0,sizeof(act));
	act.sa_handler=hdl;
	if(sigaction(SIGINT,&act,0)){
		printf("no sigterm\n");
	//return;
	}
	
	sigemptyset(&mask);
	sigaddset(&mask,SIGINT);
	if(sigprocmask(SIG_BLOCK,&mask,&orig_mask)<0){
	//return;
		printf("no sigproc\n");
	}
	*/
	/*
	uv_signal_t sig;
	uv_signal_init(loop,&sig);
	uv_signal_start(&sig,signal_handler,SIGINT);
	*/
napi_property_descriptor desc[2] = {
	{"callEmit",0, callEmit, 0, 0, 0, napi_default, 0},
	{"create_async",0,create_async, 0, 0, 0, napi_default, 0}
};
	napi_define_properties(env, exports, sizeof(desc)/sizeof(*desc), desc);
	return exports;
}
NAPI_MODULE(addon,Init)