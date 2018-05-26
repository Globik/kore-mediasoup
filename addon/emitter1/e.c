
#include <node_api.h>
#include <string.h>
#include <stdio.h>//printf
#include <stdlib.h>
#include <unistd.h> // sleep
#include <ee.h> // event emitter in C https://github.com/thlorenz/ee.c

#include <uv.h>

int a=0;
const char*event_hello="hello";

typedef struct{
napi_ref _callback;
napi_async_work _request;
}carrier;

napi_env shenv=NULL;
ee_t*ee=NULL;
napi_ref dcb;

uv_async_t async;

void on_hello(void*arg){
char*s=(char*)arg;
printf("invoked `on_hello` event with: %s\n",s);
}
napi_value fucker(){
	a++;
	napi_status k;
	printf("fucker\n");
if(shenv == NULL){printf("NULLLLLL\n"); return NULL;}
	napi_value cbu;
	
	napi_handle_scope scope;
	napi_open_handle_scope(shenv,&scope);
	napi_value argv[1];
	const char * str = "start*****************************************";
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


napi_value callEmit(napi_env env, napi_callback_info info){
	
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
	printf("Entering Execute()\n");
if(data==NULL){printf("data is null\n");return;}
	carrier*c=(carrier*)data;
	if(!c){printf("!c\n");return;}
	
	if(ee !=NULL)ee_on(ee,event_hello,on_hello);
	
	async.data=(void*)"L";
	int ab=uv_async_send(&async);
	printf("status of uv_async_send: %d\n",ab);
	
}
void print(uv_async_t*handle){
	printf("print***print: %s\n",(char*)handle->data);
	if(ee !=NULL){printf("ee is NOT NULL!!!\n"); ee_emit(ee,event_hello,"room create!\n");}
	napi_status k;
	fucker();
	fucker();
	fucker();
	printf("AAAAAAAAAAAAAAAAAAA: %d\n",a);
	}
void print_to(uv_async_t*handle){printf("print_to() occured. : %s\n",(char*)handle->data);}


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
	
    int ab=uv_async_init(loop, &async, print);
	printf("uv_async_init: %d\n", ab);
	napi_create_async_work(env, argv[1], resource_name, Execute, Complete, c, &c->_request);
	napi_queue_async_work(env, c->_request);
	return NULL;
}
void han(void){
	// don't forget into the node.js script to add the process.on('SIGINT',()=>process.exit(0))
printf("ON_EXIT occured!!!\n");
if(ee !=NULL){
ee_remove_listener(ee,event_hello,on_hello);
ee_destroy(ee);
ee=NULL;
printf("ee must be null.\n");
}
napi_status k=napi_delete_reference(shenv, dcb);
if(k==napi_ok){printf("del_ref is ok\n");}else{printf("del_ref is not ok\n");}
uv_close((uv_handle_t*)&async,NULL);
}
void cleanup(void*arg){}
int secret=7;

napi_value Init(napi_env env, napi_value exports)
{
// not available yet in node.js v 9.0
	//napi_add_env_cleanup_hook(env,cleanup,&secret,8);
	ee=ee_new();
	if(ee==NULL){printf("ee is NULL\n");}else{printf("ee is NOT NULL\n");}
	atexit(han);
napi_property_descriptor desc[2] = {
	{"callEmit",0, callEmit, 0, 0, 0, napi_default, 0},
	{"create_async",0,create_async, 0, 0, 0, napi_default, 0}
};
	napi_define_properties(env, exports, sizeof(desc)/sizeof(*desc), desc);
	return exports;
}
NAPI_MODULE(addon,Init)