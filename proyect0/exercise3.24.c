#include <stdio.h>
#include <stdlib.h>
#define numbersToReceive 10
float *getGreaterLowerNumber(float *numbers,int size){
	if(size==0)
		return NULL;
	float *greaterLowerNumber;
	int i;
	greaterLowerNumber=(float *)malloc(sizeof(float)*2);//this array contains number greater(index 0) and number lower index(1)
	*(greaterLowerNumber+0)=*(greaterLowerNumber+1)=*(numbers+0);
	for(i=0;i<size;i++){
		if(*(greaterLowerNumber+0)<*(numbers+i)){
			*(greaterLowerNumber+0)=*(numbers+i);//put as greater number
		}
		if(*(greaterLowerNumber+1)>*(numbers+i)){
			*(greaterLowerNumber+1)=*(numbers+i);//put as lower number
		}
	}
	return greaterLowerNumber;
}
void printFloatArray(float *numbers,int size,char separator){
	int i;
	for(i=0;i<size;i++){
		printf("%f%c",*(numbers+i),separator);
	}
}
int main(){
	float greaterNumber,*numbers=(float *)malloc(sizeof(float)*numbersToReceive);
	int i;
	printf("enter %d numbers\n",numbersToReceive);
	for(i=0;i<numbersToReceive;i++){
		scanf("%f",(numbers+i));
	}
	greaterNumber=getGreaterLowerNumber(numbers,numbersToReceive)[0];
	printf("list numbers ");
	printFloatArray(numbers,numbersToReceive,' ');
	printf("\ngreater number is %f\n",greaterNumber);
	return 0;
}
