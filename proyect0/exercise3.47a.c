#include <stdio.h>
double factorial(unsigned char number){
	double factorial=1;
	while(number>=1){
		factorial*=number--;
	}
	return factorial;	
}
int main(){
	unsigned char number;
	printf("enter number less than 170 but great that -1\n");
	scanf("%d",(int *)&number);
	printf("%d!=%g\n",number,factorial(number));
	return 0;
}
