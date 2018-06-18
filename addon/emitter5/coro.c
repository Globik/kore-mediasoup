// https://github.com/sjnam/lwan-coro/blob/master/basic.c
#include <stdio.h>
#include "lwan-coro.h"
void im(){}
static int func(struct coro*coro,void*data){
int i;
	for(i=1;i<=10;i++){
		printf("go\n");
	coro_yield(coro,i);
	}
	printf("ku\n");
coro_yield(coro,0);
__builtin_unreachable();
}

int main(){
int k;
	struct coro_switcher switcher;
	struct coro*coro=coro_new(&switcher,func,NULL);
	while ((k=coro_resume(coro)))
		printf("co %d\n",k);
	coro_free(coro);
	coro=NULL;
	return 0;
}