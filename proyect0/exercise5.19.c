#include <stdio.h>
int main(){
	int side,r,c;//r rows, c colums
	printf("enter side value(integer)\n");
	scanf("%d",&side);
	for(r=0;r<side;r++){
		for(c=0;c<side;c++){
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
