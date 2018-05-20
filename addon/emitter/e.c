// the original code from https://github.com/NickNaso/addon-event-emitter which is on c++
// here the same concept in plain C
#include <node_api.h>
#include <string.h>
#include <stdio.h>//printf

napi_value callEmit(napi_env env, napi_callback_info info){
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
}

napi_value Init(napi_env env, napi_value exports)
{
napi_property_descriptor desc[1] = {
	{"callEmit",0, callEmit, 0, 0, 0, napi_default, 0},
};
	napi_define_properties(env, exports, 1, desc);
	return exports;
}
NAPI_MODULE(addon,Init)