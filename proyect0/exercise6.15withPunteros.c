#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numbersToRecive 20
char containsInteger(int *array,int size,int number){
	int *i;
	i=(int *)malloc(sizeof(int));	
	for(*i=0;*i<size;*i=*i+1){
		if(*(array+(*i))==number)
			return 1;
	}
	return 0;
}
int main(){
	int *i,*entered,*aux,*numbers=(int*)malloc(sizeof(int));
	i=(int *)malloc(sizeof(int));
	entered=(int *)malloc(sizeof(int));
	aux=(int *)malloc(sizeof(int));
	*entered=1;
	for(*i=0;*i<numbersToRecive;*i=*i+1){
		printf("enter number\n");
		scanf("%d",aux);
		if(containsInteger(numbers,*entered-1,*aux))
			continue;
		*(numbers+*entered-1)=*aux;
		printf("%d added\n",*aux);
		*entered=*entered+1;
		numbers=(int*)realloc(numbers,(sizeof(int)*(*entered)));
	}
	printf("numbers in list\n");
	for(*i=0;*i<*entered-1;*i=*i+1)
		printf("%d ",*(numbers+(*i)));
	return 0;
}
