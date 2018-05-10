#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t rand32(uint32_t begin,uint32_t end){
uint32_t range=(end-begin)+1;
	uint32_t limit=((uint64_t)RAND_MAX+1)+(((uint64_t)RAND_MAX+1)%range);
	uint32_t randVal=rand();
	while(randVal >=limit) randVal=rand();
	return (randVal%range)+begin;
}
int main(){
	uint32_t a,b,c;
	a=rand32(10000000,99999999);b=rand32(10000000,99999999);c=rand32(10000000,99999999);
	printf("a: %"PRIu32"\n",a);
	printf("b: %"PRIu32"\n",b);
	printf("c: %"PRIu32"\n",c);
return 0;
}