#include <stdio.h>
int main(){
unsigned int i=1;
char*c=(char*)&i;
	if(*c){printf("little endian\n");
		  }
	else {
		printf("big endian\n");
	}
	//getchar();
	return 0;
}
// gcc -o dec dec.c