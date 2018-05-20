#include <node_api.h>
#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
#include <stdio.h>//printf
napi_env shenv=NULL;
napi_value cbi=NULL;

void fucker(){
if(shenv == NULL) return;
	napi_env env=shenv;
	const char*str="hello fucker!";
	size_t str_len=strlen(str);
	
napi_value argv[1];
	napi_create_string_utf8(env,str,str_len,argv);
	napi_value global;
	napi_get_global(env,&global);
	napi_value cbu=cbi;
napi_call_function(env,global,cbu,1,argv,NULL);
}


napi_value runcallback(napi_env env,napi_callback_info info){
size_t argc=2;
	napi_value args[2];
	napi_get_cb_info(env,info,&argc,args,NULL,NULL);
	if(argc==1){printf("ok, number of argc. Expects a single argument. %d\n",argc);}else{
	printf("argc is %d\n",argc);
	}
	napi_valuetype val0;
	napi_typeof(env,args[0],&val0);
	if(val0==napi_function){printf("OK,args[0] is a function.\n");}else{printf("args[0] is not a function.\n");}
	napi_valuetype val1;
	napi_typeof(env,args[1],&val1);
	if(val1==napi_undefined){printf("undefined.\n");}else{printf("additional args[1] should be undefined.\n");}
	//if(shenv !=NULL)return NULL;
//napi_value argv[1];
	if(shenv==NULL){
	shenv=env;
	//const char*str="hello world";
	//size_t str_len=strlen(str);
	//napi_create_string_utf8(env,str,str_len,argv);
	//napi_value global;
	//napi_get_global(env,&global);
	//napi_value cb=args[0];
	cbi=args[0];
	}
	fucker();
	//shenv=NULL;
	//cbi=NULL;
	//napi_call_function(env,global,cb,1,argv,NULL);
	return NULL;
}

napi_value runcallbacks(napi_env env,napi_callback_info info){
size_t argc=2;
	napi_value args[2];
	napi_get_cb_info(env,info,&argc,args,NULL,NULL);
	if(argc==1){printf("ok, number of argc. Expects a single argument. %d\n",argc);}else{
	printf("argc is %d\n",argc);
	}
	napi_valuetype val0;
	napi_typeof(env,args[0],&val0);
	if(val0==napi_function){printf("OK,args[0] is a function.\n");}else{printf("args[0] is not a function.\n");}
	napi_valuetype val1;
	napi_typeof(env,args[1],&val1);
	if(val1==napi_undefined){printf("undefined.\n");}else{printf("additional args[1] should be undefined.\n");}
	//if(shenv !=NULL)return NULL;
//napi_value argv[1];
	//const char*str="hello world";
	//size_t str_len=strlen(str);
	//napi_create_string_utf8(env,str,str_len,argv);
	//napi_value global;
	//napi_get_global(env,&global);
	//napi_value cb=args[0];
	fucker();
	shenv=NULL;
	cbi=NULL;
	//napi_call_function(env,global,cb,1,argv,NULL);
	return NULL;
}
napi_value Init(napi_env env,napi_value exports){
napi_property_descriptor desc[2]={
	{"runcallback",0,runcallback,0,0,0,napi_default,0},
	{"runcallbacks",0,runcallbacks,0,0,0,napi_default,0}
};
	napi_define_properties(env,exports,2,desc);
	return exports;
}
NAPI_MODULE(addon,Init)