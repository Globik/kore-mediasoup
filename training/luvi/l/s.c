///home/globik/kore-mediasoup/training/luvi/l/s.c ddd
#include "libuv.hpp"
#include "uv_callback.h"
#include "signal.h"

uv_callback_t bus, stop_worker,to_cpp;

void * on_bus(uv_callback_t*, void*);
void * stop_worker_cb(uv_callback_t*,void*);

void j_han_sig(int n){
printf("\n ON_SIG occured.\n");
uv_callback_fire(&stop_worker,NULL,NULL);
}
void*on_from_cpp(uv_callback_t*handle,void*data){
printf("ON_FROM_CPP occured. %s\n",(char*)data);
return NULL;
}

int main(){
signal(SIGINT,j_han_sig);
signal(SIGTERM,j_han_sig);
ini();
printi();
int rc=uv_callback_init(get_loopi(), &bus,on_bus, UV_DEFAULT);
printf("rc init: %d\n",rc);
rc=uv_callback_fire(&bus,(void*)"MAMA", NULL);
printf("rc fire: %d\n",rc);
	
rc=uv_callback_init(get_loopi(), &to_cpp,trans_to_cpp, UV_DEFAULT);
printf("rc to_cpp init: %d\n",rc);

rc=uv_callback_fire(&to_cpp,(void*)"CPP IS OK?", NULL);
printf("rc to_cpp fire: %d\n",rc);
	
rc=uv_callback_init(get_loopi(),&stop_worker,stop_worker_cb,UV_COALESCE);
printf("rc init stop_worker: %d\n",rc);
runi();
destri();
printf("Bye.\n");
return 0;
}

void * on_bus(uv_callback_t*cb, void*data){
printf("ON_BUS occured. %s\n", (char*)data);
return NULL;
}
void * stop_worker_cb(uv_callback_t*handle,void*arg){
printf("ON_STOP worker cb\n");
uv_stop(((uv_handle_t*)handle)->loop);
return NULL;
}