
#include <cstdio>  // sprintf()
#include <cstring> // std::memmove()
#include <sstream> // std::ostringstream
#include <string>
#include <unistd.h>
#include <iostream> //cout
#include <stdlib.h> // free()
#include <jansson.h>
void dm(void*);
int main(){
std::string str1="\"{\"dama\":\"lakkkkkkkkkkkkkkkkkkkkkkkkkkkkkpa\"}\"";
std::string str="{\"mama\":\"papa\"}";
char*chr=strdup(str.c_str());
std::printf("chr: %s\n",chr);
//dm(chr);
//free(chr);
dm((void*)chr);
//free(chr);
chr=strdup(str1.c_str());
//std::printf("chr: %s\n",chr);
//free(chr);	
dm((void*)chr);
//free(chr);
	
std::printf("end\n");
return 0;
}

void dm(void*me){
std::printf("chr 2: %s\n",(char*)me);
char*l=(char*)me;

json_auto_t*reply=json_object();
json_object_set_new(reply,"type",json_string("on_result"));
json_object_set_new(reply,"msg",json_string(l));
size_t size=json_dumpb(reply,NULL,0,0);
if(size==0) { 
free((char*)me);
	return;}
char *buf=(char*)alloca(size);
size=json_dumpb(reply,buf,size,0);
std::cout << buf << std::endl;
std::printf("Size: %d\n",size);
//free(me);

//free(char*)me);
free(me);
std::printf("after : %s\n",(char*)me);
std::printf("after l: %s\n",l);

}
/*

g++ -o js js.cpp
*/