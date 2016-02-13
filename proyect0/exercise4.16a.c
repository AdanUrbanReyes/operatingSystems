#include <stdio.h>
#define columns 10
int main(){
	int c;
	int i=1;
	for(c=0;c<columns;c++){
		for(i=0;i<=c;i++){
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
