#include <stdio.h>
#include <stdlib.h>
int main(){
	int *side,*r,*c;//r rows, c colums
	side=(int*)malloc(sizeof(int));
	r=(int*)malloc(sizeof(int));
	c=(int*)malloc(sizeof(int));
	printf("enter side value(integer)\n");
	scanf("%d",side);
	for(*r=0;*r<*side;*r=*r+1){
		for(*c=0;*c<*side;*c=*c+1){
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
