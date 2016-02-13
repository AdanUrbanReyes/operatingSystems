#include <stdio.h>
int main(){
	int number;
	printf("enter number\n");
	scanf("%d",&number);
	if(number%2==0)
		printf("%d is par\n",number);
	else
		printf("%d is odd\n",number);
	return 0;
}
