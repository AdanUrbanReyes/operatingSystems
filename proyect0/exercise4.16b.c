#include <stdio.h>
#define columns 10
int main(){
	int c;
	int i=1;
	for(c=columns;c>0;c--){
		for(i=c;i>0;i--){
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
