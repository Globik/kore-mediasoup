
#include <node_api.h>
#include <string.h>
#include <stdio.h>//printf
#include <stdlib.h>

#include <uv.h>

#include "uv_callback.h"
int a=0;
uv_callback_t cb_sum;

typedef struct{
napi_ref _callback;
napi_async_work _request;
}carrier;

napi_env shenv=NULL;
napi_value cb_id=NULL;

uv_async_t async;

void*on_sum(uv_callback_t*cb,void*data){
printf("on_sum occured: %s\n",(char*)data);
//try here emit ev to nodejs
return NULL;
}


napi_value fucker(){
	a++;
	printf("fucker\n");
if(shenv == NULL) return NULL;
	napi_env env=shenv;
	napi_value argv[1];
   napi_value data;
	napi_handle_scope scope;
	napi_open_handle_scope(env,&scope);
	const char * str = "start";
	size_t str_len = strlen(str);
	printf("suka\n");
	napi_status k=napi_create_string_utf8(env, str, str_len, argv);
	if(k==napi_ok){printf("cr_str1 is ok\n");}else{printf("cr_str1 is not ok\n");}
	
	const char * str2 = "'Some data string came from a n-api addon in plain C, ***!'";
	size_t str_len2 = strlen(str2);
	
	k=napi_create_string_utf8(env, str2, str_len2, &data);
	if(k==napi_ok){printf("cr_str2 is ok\n");}else{printf("cr_str2 is not ok\n");}
	
//napi_value argv[1];
	//napi_create_string_utf8(env,str,str_len,argv);
	napi_value global;
	k=napi_get_global(env,&global);
	if(k==napi_ok){printf("get_glob is ok\n");}else{printf("get_glob is not ok\n");}
	
	napi_value cbu=cb_id;
    k=napi_call_function(env, global, cbu, 2, argv,NULL);
	if(k==napi_ok){printf("call_func is ok\n");}else{printf("call_func is not ok\n");}
	
	k=napi_close_handle_scope(env,scope);
	if(k==napi_ok){printf("close_scope is ok\n");}else{printf("close_scope is not ok\n");}
	
	return data;
	
}


napi_value callEmit(napi_env env, napi_callback_info info){
	
	//int rc=uv_callback_fire(&cb_sum,(void*)"string",NULL);
	//printf("&cb_sum fire: %d\n",rc);
	
	
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
	if(shenv==NULL)shenv=env;
	cb_id=args[0];
	
	/*
   napi_value argv[1];
   napi_value data;
	const char * str = "start";
	size_t str_len = strlen(str);
	napi_create_string_utf8(env, str, str_len, argv);
	
	const char * str2 = "'Some data string came from a n-api addon in plain C, ***!'";
	size_t str_len2 = strlen(str2);
	napi_create_string_utf8(env, str2, str_len2, &data);
	
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
	return data;
	*/
	//fucker();
	//fucker();
	//fucker();
	
	return NULL;
}

void Execute(napi_env env, void*data){
	printf("Entering Execute()\n");
	//uv_loop_t *loop;
if(data==NULL){printf("data is null\n");return;}
	carrier*c=(carrier*)data;
	if(!c){printf("!c\n");return;}
	/*
	napi_status status=napi_get_uv_event_loop(env,&loop);
	if(status==napi_ok){
		printf("loop is ok\n");
	}else{
		printf("loop is NOT ok\n");
		return;
	}
	
	uv_loop_init(loop);
	*/
//	int r=uv_callback_fire(&cb_sum,(void*)"string",NULL);
//	printf("&cb_sum fire: %d\n",r);
	/*
	int rc=uv_callback_init(loop, &cb_sum,on_sum,UV_DEFAULT);
	printf("rc init: %d\n",rc);
	if(rc !=0)return;
	printf("Blah.\n");
	int r=uv_callback_fire(&cb_sum, NULL, NULL);
	printf("&cb_sum fire: %d\n",r);
	uv_run(loop,UV_RUN_DEFAULT);
	r=uv_callback_fire(&cb_sum, NULL, NULL);
	printf("&cb_sum fire: %d\n",r);
	//if(rc !=0)return;
	*/
	async.data=(void*)"L";
	uv_async_send(&async);
	
	
}
void print(uv_async_t*handle){
	printf("print***print: %s\n",(char*)handle->data);
	fucker();
	fucker();
	fucker();
	printf("AAAAAAAAAAAAAAAAAAA: %d\n",a);
	//uv_close((uv_handle_t*)&async,NULL);
	
}
void Complete(napi_env env,napi_status status,void*data){
	printf("Entering Complete()\n");
    carrier*c=(carrier*)data;
	if(status !=napi_ok){printf("status is NOT OK.\n");return;}else{printf("status is ok\n");}
	napi_value argv[2];
	napi_value callbac;
	napi_status k=napi_get_reference_value(env,c->_callback, &callbac);
	if(k==napi_ok)printf("get_ref is ok\n");
	napi_value globali;
	k=napi_get_global(env,&globali);
	if(k==napi_ok)printf("get_glob is ok\n");
	napi_value result;
	if(status==napi_ok)printf("status is ok\n");
	k=napi_call_function(env, globali, callbac, 2, argv,&result);
	if(k==napi_ok){printf("call_func is ok\n");}else{printf("call_func is not ok\n");}
	
	
	printf("deleting reference\n");
	k=napi_delete_reference(env,c->_callback);
	if(k==napi_ok){printf("del_ref is ok\n");}else{printf("del_ref is not ok\n");}
	k=napi_delete_async_work(env,c->_request);
	if(k==napi_ok){printf("del_work is ok\n");}else{printf("del_work is not ok\n");}
	//free(c);
	// m
	//uv_close((uv_handle_t*)&async,NULL);
	//return;
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
	
	//int rc=uv_callback_init(loop, &cb_sum,on_sum,UV_DEFAULT);
	//printf("rc init: %d\n",rc);
	napi_get_cb_info(env,info,&argc,argv, &_this, &data);
	napi_create_reference(env, argv[2], 1, &c->_callback);
	napi_create_string_utf8(env,"testi",NAPI_AUTO_LENGTH,&resource_name);
	
uv_async_init(loop,&async,print);
	
	napi_create_async_work(env, argv[1], resource_name, Execute, Complete, c, &c->_request);
	napi_queue_async_work(env, c->_request);
	
	//int rc=uv_callback_fire(&cb_sum,(void*)"string",NULL);
	//printf("&cb_sum fire: %d\n",rc);
	//if(rc !=0)return NULL;
	return NULL;
}
napi_value Init(napi_env env, napi_value exports)
{
napi_property_descriptor desc[2] = {
	{"callEmit",0, callEmit, 0, 0, 0, napi_default, 0},
	{"create_async",0,create_async, 0, 0, 0, napi_default, 0}
};
	napi_define_properties(env, exports, sizeof(desc)/sizeof(*desc), desc);
	return exports;
}
NAPI_MODULE(addon,Init)