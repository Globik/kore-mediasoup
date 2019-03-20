#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>

#include <stdint.h>

#include <sys/un.h>
#include <sys/types.h>
#include <node_api.h>
#include <uv.h>
#define green "\x1b[32m"
#define rst "\x1b[0m"
#define red "\x1b[31m"
#define yel "\x1b[33m"
//#define socket_name "/home/globik/fuck"
static uv_poll_t sockin_watcher,sockout_watcher;
static uv_os_sock_t data_socket=0;
static volatile int uv_poll_init_success=0;
int fucker=0;
bool is_read=true;
bool is_fuck=false;

napi_env shenv=NULL;
napi_ref dcb;

napi_env msgEnv=NULL;
napi_ref msgCb;
napi_value on_msg_cb(char*);
uv_loop_t *loop=NULL;

napi_value pfucker(void);
static void on_sock_read(uv_poll_t*,int,int);
static void on_sock_write(uv_poll_t*,int,int);
static int write_start(char*,size_t);

static void on_clo(uv_handle_t*);
static void at_pexit(void);
static int sockfd_init(char*);
static int uvpoll_init(napi_env);
static void uvpoll_cleanup(void);


static void uvpoll_cleanup(){
//printf(green "uvpoll_cleanup() occured.\n" rst);
if(uv_poll_init_success==0){ 
printf(yel "[%s:%d] uv_poll_init_success: %d\n" rst, __FILE__, __LINE__, uv_poll_init_success);return;
}
else{
printf(yel "[%s:%d] sucess init: %d\n" rst, __FILE__, __LINE__, uv_poll_init_success);
}
if(is_read){
printf(yel "[%s:%d] IS_READ IS TRUE\n" rst, __FILE__, __LINE__);
uv_poll_stop(&sockout_watcher);//must be active
}
uv_poll_stop(&sockin_watcher);
uv_close((uv_handle_t*)&sockout_watcher, on_clo);
uv_close((uv_handle_t*)&sockin_watcher, on_clo);
printf(yel "[%s:%d] data_socket end: %d\n" rst, __FILE__, __LINE__, data_socket);
close(data_socket);
data_socket=0;
uv_poll_init_success=0;
} 
static void on_clo(uv_handle_t*h){
printf(yel "[%s:%d] ****on_clo occured.****\n" rst, __FILE__, __LINE__);
printf(yel "[%s:%d] handle: %p, h->data: %p\n" rst, __FILE__, __LINE__, h, h->data);
if(h->data){
printf(yel "[%s:%d] h->data %s\n" rst, __FILE__, __LINE__, (char*)h->data);

if(h->data !=NULL) free(h->data);
}
}

static int sockfd_init(char*socket_name){
int ret;
struct sockaddr_un addr;
data_socket=socket(AF_UNIX,SOCK_SEQPACKET | O_NONBLOCK,0);
if(data_socket==-1){
fprintf(stderr,red "[%s:%d] data_socket err: %d\n" rst, __FILE__, __LINE__, data_socket);
perror("socket");
return -1;
}
memset(&addr,0,sizeof(struct sockaddr_un));
addr.sun_family=AF_UNIX;
strncpy(addr.sun_path,socket_name,sizeof(addr.sun_path)-1);
ret=connect(data_socket,(const struct sockaddr*)&addr,sizeof(struct sockaddr_un));
if(ret==-1){
fprintf(stderr,red "[%s:%d] the server is down.%d\n" rst, __FILE__, __LINE__, ret);
if(data_socket !=0)close(data_socket);
data_socket=0;
return -1;
}
return 0;
}
static int uvpoll_init(napi_env env){
if(data_socket <=0) {printf(red "[%s:%d] data_socket is undefined\n" rst, __FILE__, __LINE__);return -1;}
napi_status status=napi_get_uv_event_loop(env,&loop);
if(status==napi_ok){
fprintf(stderr, yel "[%s:%d] get_uv_event_loop is OK\n" rst, __FILE__, __LINE__);
}else{
fprintf(stderr,red "[%s:%d] get_uv_event_loop is NOT OK!\n" rst, __FILE__,  __LINE__);
if(data_socket !=0){close(data_socket);data_socket=0;}
return -1;
}
	//int kak=uv_loop_alive(loop);
	//printf("IS ALIVE2: %d\n",kak);
int s=uv_poll_init(loop, &sockin_watcher, data_socket);
if(0 !=s){
perror("poll init failed: ");
fprintf(stderr,red "[%s:%d] uv_poll init failed\n" rst, __FILE__, __LINE__);
if(data_socket !=0)close(data_socket);
return -1;
}
s=uv_poll_init(loop, &sockout_watcher, data_socket);
if(0 !=s){
perror("sockout_watcher init failed.");
uv_poll_stop(&sockin_watcher);
if(data_socket !=0)close(data_socket);
return -1;
}
uv_poll_init_success = 1;
uv_poll_start(&sockout_watcher, UV_READABLE/* | UV_DISCONNECT*/, on_sock_read);
return 0;
}

static int write_start(char*s, size_t leni){
if(!is_read){
	printf(yel "[%s:%d] write_start is_read false\n" rst, __FILE__, __LINE__);
	}else{
	printf(yel "[%s:%d] write_start is_read true\n" rst, __FILE__, __LINE__);
	}
	//printf("before stop sockout\n");
uv_poll_stop(&sockout_watcher);
//printf("after stop sockout\n");
is_read=false;
printf(green "read_start leni:: %d\n" rst, leni);
//char*s="str HERE.";
sockin_watcher.data=NULL;
sockin_watcher.data=strdup(s);
uv_poll_start(&sockin_watcher, UV_WRITABLE, on_sock_write);
//printf("after poll start sockin\n");
return 0;
}

static void on_sock_read(uv_poll_t*watcher,int status,int revents){
size_t bs=512*6;
char buffer[BUFSIZ];
printf(yel "[%s:%d] on_sock_read: revents: %d, status: %d\n" rst, __FILE__, __LINE__, revents, status);
if(status !=0){printf(red "[%s:%d] status: %d\n" rst, __FILE__, __LINE__, status);return;}

if(revents == UV_READABLE){
		
int ret=read(data_socket, buffer, sizeof(buffer));
if(ret==-1){
perror("read");
fprintf(stderr,red "[%s:%d] read error occured in sock_read. %d\n" rst, __FILE__, __LINE__, ret);
return;
}
if(ret==0){
on_msg_cb("{\"err\":\"connection closed\",\"type\":\"sqpacksock_error\",\"event\":\"closed\"}");
printf(red "[%s:%d] ret is NULL***\n" rst, __FILE__, __LINE__);
uvpoll_cleanup();
return;
}
printf(yel "[%s:%d] ret in read: %d\n" rst, __FILE__, __LINE__, ret);
printf(yel "[%s:%d] BUFSIZ: %u\n" rst, __FILE__, __LINE__, BUFSIZ);
if(ret > (3071)){printf(yel "[%s:%d]Achtung! ret > sizeof(bufrer) %d\n" rst, __FILE__,__LINE__, (512*6));}
buffer[ret]=0;
//fprintf(stderr,"result => %s\n",buffer);
on_msg_cb(buffer);
memset(buffer,0,bs);
}
}

int buka=0;

static void on_sock_write(uv_poll_t*watcher,int status,int mevents){
buka++;
	int ret;
if(status !=0){
if(watcher->data !=NULL)free(watcher->data);
watcher->data=NULL;
printf(red "[%s:%d]on_sock_write: status: %d\n" rst,__FILE__, __LINE__, status);
return;
}

//printf("BUKA write_sock: %d\n", buka);
printf(yel "[%s:%d]on_sock_write: MEVENTS: %d STATUS: %d\n" rst,__FILE__, __LINE__, mevents, status);
if(mevents == UV_WRITABLE){
//fprintf(stderr, "Uv writable\n");
	//TODO check buffer overflow
	//size_t bs=512*6;
char buf[BUFSIZ];
if(watcher->data !=NULL){
char*s=watcher->data;
//printf("watcher->data: %s\n",s);
strcpy(buf,s);
free(s);
watcher->data=NULL;
//buf[BUFSIZ]=0;
int leni=strlen(buf);
printf(yel "[%s:%d]leni in write is %d\n" rst,__FILE__, __LINE__,leni);
ret=send(data_socket, buf, leni, 0);
if(ret==-1){
printf(red "[%s:%d] in write ret:: %d\n" rst, __FILE__, __LINE__, ret);
perror("write2");
}
//printf("leni: %d, ret: %d\n",leni,ret);
}
memset(buf,0, BUFSIZ);
}
uv_poll_stop(&sockin_watcher);
uv_poll_start(&sockout_watcher, UV_READABLE, on_sock_read);
is_read=true;
pfucker();
}

napi_value p_init(napi_env env, napi_callback_info info)
{
	char buf[128];
	size_t bs=128;
	size_t cop;
napi_value global;
napi_status status;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);
/*
napi_valuetype val0;
napi_typeof(env, args[1], &val0);
if(val0 == napi_function){
printf("OK, args[1] is a function.\n");
}else{
printf("args[1] is not a function.\n");
}
*/
napi_value argv[2];
napi_valuetype vstr;
napi_typeof(env,args[0],&vstr);
if(vstr==napi_string){
//printf("is a String.\n");
	

status=napi_get_value_string_utf8(env,args[0],buf,bs,&cop);
if(status !=napi_ok){
printf(red "[%s:%d] status get str is NOT ok!\n" rst, __FILE__, __LINE__);return NULL;
}
	buf[cop]=0;
	//printf("strbuf: %s\n",buf);
}else{
printf(red "[%s:%d] is not a string.\n" rst, __FILE__, __LINE__);
const char * str4 = "Is not a string.";
size_t str_len4 = strlen(str4);
napi_create_string_utf8(env, str4, str_len4, &argv[0]);
napi_get_null(env,&argv[1]);
	
napi_get_global(env, &global);
napi_value cb = args[1];
napi_status status = napi_call_function(env, global, cb, 2, argv, NULL);
if(status != napi_ok){
printf(red "[%s:%d] napi_status is NOT OK! CALL Function*** _FUNC\n" rst, __FILE__, __LINE__);

}
return NULL;
}


//napi_value argv[2];
int a=sockfd_init(buf);
int b=uvpoll_init(env);
//printf(green "sockfd_init(): %d\n" rst, a);
//printf("uvpoll_init(); %d\n",b);
if((a || b) !=0){
printf(red "[%s:%d] server is down!\n" rst, __FILE__, __LINE__);
//napi_fatal_error("p_init",NAPI_AUTO_LENGTH,"not connected.",NAPI_AUTO_LENGTH);
//napi_throw_error(env,NULL,"No Server.");
const char * str = "Server is down. Or uv_poll failed.";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, &argv[0]);
napi_get_null(env,&argv[1]);
}

if((a&&b)==0){ 
	//printf("A&&B==0!\n");
const char * str3 = "start_result";
size_t str_len3 = strlen(str3);
napi_create_string_utf8(env, str3, str_len3, &argv[1]);
napi_get_null(env,&argv[0]);
}
napi_value globa;
napi_get_global(env, &globa);
napi_value cb = args[1];

status = napi_call_function(env, globa, cb, 2, argv, NULL);
if(status != napi_ok){
printf(red "[%s:%d] call_func p_init is NOT OK!\n" rst, __FILE__, __LINE__);
return NULL;
}
return NULL;
}


napi_value pfucker(){
napi_status k;
if(shenv == NULL){printf(red "[%s:%d] shenv is NULL in pfucker()\n" rst, __FILE__, __LINE__); return NULL;}
napi_value cbu;
napi_handle_scope scope;
napi_open_handle_scope(shenv,&scope);
napi_value argv[1];
const char * str = "now_readable";
size_t str_len = strlen(str);
k=napi_create_string_utf8(shenv, str, str_len, argv);
if(k !=napi_ok){printf(red "[%s:%d] cr_str1 pfucker() is NOT ok!\n" rst, __FILE__, __LINE__);return NULL;}
k=napi_get_reference_value(shenv, dcb, &cbu);
if(k !=napi_ok){printf(red "[%s:%d] get_ref pfucker() is NOT ok!\n" rst, __FILE__, __LINE__);return NULL;}
napi_value global;
k=napi_get_global(shenv,&global);
if(k !=napi_ok){printf(red "[%s:%d] get_glob is NOT ok!\n" rst, __FILE__, __LINE__);return NULL;}
k=napi_call_function(shenv, global, cbu, 2, argv,NULL);
if(k !=napi_ok){printf(red "[%s:%d] call_func is pfucker() NOT ok!\n" rst, __FILE__, __LINE__);return NULL;}
k=napi_close_handle_scope(shenv,scope);
if(k !=napi_ok){printf(red "[%s:%d] close_scope pfucker() is NOT ok!\n" rst, __FILE__, __LINE__);}
return NULL;
}
//to node.js a message send
napi_value on_msg_cb(char*msg_str){
napi_status k;
if(msgEnv == NULL){printf(red "[%s:%d] msgEnv is NULL.\n" rst, __FILE__, __LINE__); return NULL;}
napi_value cbu;
napi_handle_scope scope;
napi_open_handle_scope(msgEnv,&scope);
napi_value argv[1];
const char * str = msg_str;//"now_readable";
size_t str_len = strlen(str);
k=napi_create_string_utf8(msgEnv, str, str_len, argv);
if(k !=napi_ok){printf(red "[%s:%d] cr_str1 in on_msg_cb is NOT ok!\n" rst, __FILE__, __LINE__);
			//return NULL;
			   }
k=napi_get_reference_value(msgEnv, msgCb, &cbu);
if(k !=napi_ok){
printf(red "[%s:%d] get_ref in on_msg_cb is NOT ok!\n" rst, __FILE__, __LINE__);
			//return NULL;
			   }
napi_value global;
k=napi_get_global(msgEnv,&global);
if(k !=napi_ok){printf(red "[%s:%d] get_glob in on_msg_cb is NOT ok!\n" rst, __FILE__, __LINE__);
				//return NULL;
			   }
if(shenv !=NULL){
	printf(yel "[%s:%d] shenv is not null.\n" rst, __FILE__, __LINE__);
	}else{
	printf(yel "[%s:%d] shenv is NULL ok\n" rst, __FILE__, __LINE__);
	}
k=napi_call_function(msgEnv, global, cbu, 2, argv, NULL);
if(k !=napi_ok){printf(red "[%s:%d] call_func in on_msg_cb is NOT ok!\n" rst, __FILE__, __LINE__);
//return NULL;
}
k=napi_close_handle_scope(msgEnv,scope);
if(k !=napi_ok){
printf(red "[%s:%d] close_scope is not ok\n" rst, __FILE__, __LINE__);
}
return NULL;
}
napi_value p_close(napi_env env, napi_callback_info info)
{
if(uv_poll_init_success==0)return NULL;
napi_status k;

size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);
/*
napi_valuetype val0;
napi_typeof(env, args[0], &val0);
if(val0 == napi_function){
printf("OK, args[0] is a function.\n");
}else{
printf("args[0] is not a function.\n");
}
*/
uvpoll_cleanup();
if(shenv !=NULL){
printf(yel "[%s:%d] shenv is not NULL\n" rst, __FILE__, __LINE__);
//int kak=uv_loop_alive(loop);
//printf("IS ALIVE: %d\n",kak);
k=napi_delete_reference(shenv, dcb);
if(k !=napi_ok){
printf(red "[%s:%d] del_ref in p_close is NOT ok!\n" rst, __FILE__, __LINE__);
}
shenv=NULL;	
}
if(msgEnv !=NULL){
//printf("msgEnv is NOT NULL.\n");
k=napi_delete_reference(msgEnv, msgCb);
if(k==napi_ok){ 
printf(yel "[%s:%d] del_ref msgCb is OK.\n" rst, __FILE__, __LINE__);
}else{
printf(red "[%s:%d] del_ref msgCb is NOT OK.\n" rst, __FILE__, __LINE__);
}
msgEnv=NULL;	
}
napi_value argv[1];

const char * str = "close_result";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){
printf(red "[%s:%d] call_func in p_close[result] is NOT OK!\n" rst, __FILE__, __LINE__);
return NULL;
}
return NULL;
}

napi_value on_ready(napi_env env,napi_callback_info info){
if(uv_poll_init_success==0)return NULL;
napi_status k;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);


/*napi_valuetype val0;
napi_typeof(env, args[0], &val0);
if(val0 == napi_function){
printf("OK, args[0] is a function.\n");
}else{
printf("args[0] is not a function.\n");
}
*/

if(shenv==NULL){
//printf("SHENV is NULL\n");
shenv=env;
}
napi_value argv[1];
k=napi_create_reference(env, args[0], 10, &dcb);
if(k !=napi_ok){printf(red "[%s:%d] create reference in on_ready is NOT ok\n" rst, __FILE__, __LINE__);return NULL;}
const char * str = "start ****ON_READY****";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){
printf(red "[%s:%d] call_func in on_reay is NOT OK!\n" rst, __FILE__, __LINE__);
shenv=NULL;
return NULL;
}
return NULL;
}
napi_value p_send(napi_env env, napi_callback_info info)
{
//if(uv_poll_init_success==0)return NULL;
napi_status k;
size_t argc = 2; // input buffer and callback
napi_value args[2]; // callback
napi_get_cb_info(env, info, &argc, args, NULL, NULL);

//napi_handle_scope scope;
//napi_open_handle_scope(env,&scope);
//const unsigned char*input;
char*input;char*muka;
size_t len;
bool is_buf;
k=napi_is_buffer(env,args[0],&is_buf);
if(k !=napi_ok){printf( red "[%s:%d] status buf failed.\n" rst, __FILE__, __LINE__);return NULL;}
if(is_buf){
//printf("IS BUFFER!\n");
k=napi_get_buffer_info(env,args[0],(void**)(&input),&len);
if(k !=napi_ok){
printf(red "[%s:%d] failed to get buffer info input.\n" rst, __FILE__, __LINE__);
return NULL;
}
//printf("length: %d\n",len);
input[len]=0;
muka=input;
//printf("INPUT: %s\n",muka);
}else{
printf(red "[%s:%d] IS NOT A BUFFER\n" rst, __FILE__, __LINE__);
return NULL;
}
//len=0;
/*	
napi_valuetype val0;
napi_typeof(env, args[1], &val0);
if(val0 == napi_function){
printf("OK, args[1] is a function.\n");
}else{
printf("args[1] is not a function.\n");
}
*/
if(uv_poll_init_success==0){
printf(red "[%s:%d] FD_POLL is NOT initialised.\n" rst, __FILE__, __LINE__);
return NULL;
}
napi_value argv[2];// for cb args: err, data

if(is_read){
	
//int kak=uv_loop_alive(loop);
//printf("IS ALIVE_#############: %d\n",kak);
int mu=write_start(muka,len);
printf("[%s:%d] write start is OK? %d\n", __FILE__, __LINE__, mu);
const char * str = "write_result";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, &argv[1]);
napi_get_null(env,&argv[0]);
}else{
const char * str = "what_the_fuck";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, &argv[0]);
napi_get_null(env,&argv[1]);
}

napi_value global;
napi_get_global(env, &global);
napi_value cb = args[1];//args[0] is an input buffer, args[1] is output -> callback(err,data)=>err is &argv[0], data is &argv[1]

k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){
printf(red "[%s:%d] call_func in p_send is NOT ok!\n" rst, __FILE__, __LINE__);
}
//k=napi_close_handle_scope(env,scope);
//if(k==napi_ok){printf("close_scope is ok\n");}else{printf("close_scope is not ok\n");}
return NULL;
}

napi_value on_msg(napi_env env,napi_callback_info info){
//printf("****ONONON MSG MSG***\n");
if(uv_poll_init_success==0)return NULL;
napi_status k;
size_t argc = 2;
napi_value args[2];
napi_get_cb_info(env, info, &argc, args, NULL, NULL);

if(msgEnv==NULL){
msgEnv=env;
}
napi_value argv[1];
k=napi_create_reference(env, args[0], 2, &msgCb);
if(k !=napi_ok){printf(red "[%s:%d] create reference on_msg is not ok.\n" rst, __FILE__, __LINE__);return NULL;}
const char * str = "on_msg prepare";
size_t str_len = strlen(str);
napi_create_string_utf8(env, str, str_len, argv);
napi_value global;
napi_get_global(env, &global);
napi_value cb = args[0];
k = napi_call_function(env, global, cb, 2, argv, NULL);
if(k != napi_ok){
printf(red "[%s:%d] call_func on_msg is NOT ok!\n" rst, __FILE__, __LINE__);
msgEnv=NULL;
return NULL;
}
return NULL;
}

static void at_pexit(){
printf(yel "[%s:%d] at_exit cb occured.\n", __FILE__, __LINE__);
//uvpoll_cleanup();
}

napi_value Init(napi_env env, napi_value exports)
{
atexit(at_pexit);
	napi_status status;
	napi_value fn,fn1,fn2,fn3,fn4;
	status=napi_create_function(env,NULL,0,p_init,NULL,&fn);
	if(status !=napi_ok){printf(red "[%s:%d] create func p_init fail.\n" rst, __FILE__, __LINE__);return NULL;}
	status=napi_set_named_property(env,exports,"p_init",fn);
	if(status !=napi_ok){printf(red "[%s:%d] set prop p_init fail.\n" rst, __FILE__, __LINE__);return NULL;}
	
	status=napi_create_function(env,NULL,0, p_send,NULL,&fn1);
	if(status !=napi_ok){printf(red "[%s:%d] create func p_send fail.\n" rst, __FILE__, __LINE__);return NULL;}
	status=napi_set_named_property(env,exports,"p_send",fn1);
	if(status !=napi_ok){printf(red "[%s:%d] set prop p_send fail.\n" rst, __FILE__, __LINE__);return NULL;}
	
	status=napi_create_function(env,NULL,0,p_close,NULL,&fn2);
	if(status !=napi_ok){printf(red "[%s:%d] create func p_close fail.\n" rst, __FILE__, __LINE__);return NULL;}
	status=napi_set_named_property(env,exports,"p_close",fn2);
	if(status !=napi_ok){printf(red "[%s:%d] set prop p_close fail.\n" rst, __FILE__, __LINE__);return NULL;}
	
	status=napi_create_function(env,NULL,0,on_ready,NULL,&fn3);
	if(status !=napi_ok){printf(red "[%s:%d] create func on_ready fail.\n" rst, __FILE__, __LINE__);return NULL;}
	status=napi_set_named_property(env,exports,"on_ready",fn3);
	if(status !=napi_ok){printf(red "[%s:%d] set prop on_ready fail.\n" rst, __FILE__, __LINE__);return NULL;}
	
	status=napi_create_function(env,NULL,0,on_msg,NULL,&fn4);
	if(status !=napi_ok){printf(red "[%s:%d] create func on_msg fail.\n" rst, __FILE__, __LINE__);return NULL;}
	status=napi_set_named_property(env,exports,"on_msg",fn4);
	if(status !=napi_ok){printf(red "[%s:%d] set prop on_msg fail.\n" rst, __FILE__, __LINE__);return NULL;}
return exports;
}
NAPI_MODULE(addon,Init)
