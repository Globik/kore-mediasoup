#include <stdio.h>
#include <stdlib.h>

#include "lwan-coro.h"

#define max_line 256
struct file{
char*name;
	char*line;
};
static int producer(struct coro*coro,void*data){
struct file*f=(struct file*)data;
	FILE*fp=fopen(f->name,"r");
	if(!fp){
	fprintf(stderr,"file does not exists %s\n",f->name);
		return 0;
	}
	f->line=coro_malloc(coro,max_line);
	while(fgets(f->line,max_line,fp)) coro_yield(coro,1);
	fclose(fp);
	fp=NULL;
	return 0;
}
int main(){
struct coro_switcher switcher;
	struct coro*coro=NULL;
	struct file f={.name="binding.gyp"};
	coro=coro_new(&switcher,producer,&f);
	while(coro_resume(coro)) printf("%s\n",f.line);
	coro_free(coro);
	coro=NULL;
	exit(EXIT_SUCCESS);
}