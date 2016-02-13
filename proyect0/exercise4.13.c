/*
   calcula and print the product the integers impares of 1 to 15
*/
#include <stdio.h>
#define limitUp 15
#define limitDown 1
int main(){
	int i,product=1;
	for(i=limitDown;i<=limitUp;i++){
		if(i%2!=0)
			product*=i;
	}
	printf("product of impares %d-%d is %d\n",limitDown,limitUp,product);
	return 0;
}
