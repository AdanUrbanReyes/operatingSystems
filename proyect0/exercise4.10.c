/*
	this program calcula average of numbers entered by keyboard but just with numbers that preceden of last number entered
	example
	4 2 8 10 9
	response 4+2+8/3 =4.666
	not take in cuenta 10 becose not precede that 9 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>//use for functions realloc
void printFloatArray(float *array,int size,char separator){
	int i;
	for(i=0;i<size;i++){
		printf("%g%c",*(array+i),separator);
	}
}
int main(){
	float *numbers=(float *)malloc(sizeof(float)),average=0;
	int i,numbersEntered=0,numbersPreceden=0;
	char option[3];
	do{
		printf("would you like insert other number? yes/not\n");
		scanf("%s",option);
		if(strncasecmp(option,"y",1))
			continue;
		printf("enter number\n");
		scanf("%f",(numbers+(numbersEntered)));
		numbersEntered++;
		numbers=(float *)realloc(numbers,sizeof(float)*(numbersEntered+1));
	}while(strncasecmp(option,"n",1));
	printFloatArray(numbers,numbersEntered,' ');
	for(i=0,numbersPreceden=0;i<numbersEntered-1;i++){
		if(*(numbers+i)<*(numbers+(numbersEntered-1))){
			average+=*(numbers+i);
			numbersPreceden++;
		}
	}
	if(average!=0)
		average/=numbersPreceden;
	printf("\naverage of numbers that precede of %g=%g\n",*(numbers+(numbersEntered-1)),average);
	return 0;
}
