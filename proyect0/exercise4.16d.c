#include <stdio.h>
#define columns 10
int main(){
	int c;
	int i,j;
	for(c=1;c<=columns;c++){
		for(j=0;j<columns-c;j++)
			printf(" ");
		for(i=0;i<c;i++)
			printf("*");
		printf("\n");
	}
	return 0;
}
