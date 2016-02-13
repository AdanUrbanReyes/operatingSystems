#include <stdio.h>
#define columns 10
int main(){
	int c;
	int i,j;
	for(c=columns;c>0;c--){
		for(j=0;j<columns-c;j++)
			printf(" ");
		for(i=c;i>0;i--)
			printf("*");
		printf("\n");
	}
	return 0;
}
