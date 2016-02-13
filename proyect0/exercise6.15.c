#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define numbersToRecive 20
char containsInteger(int *array,int size,int number){
	int i;
	for(i=0;i<size;i++){
		if(*(array+i)==number)
			return 1;
	}
	return 0;
}
int main(){
	int i,entered=1,aux,*numbers=(int*)malloc(sizeof(int));
	for(i=0;i<numbersToRecive;i++){
      printf("enter number\n");
      scanf("%d",&aux);
		if(containsInteger(numbers,entered-1,aux))
			continue;
		*(numbers+entered-1)=aux;
		printf("%d added\n",aux);
      entered++;
      numbers=(int*)realloc(numbers,(sizeof(int)*entered));
	}
	printf("numbers in list\n");
	for(i=0;i<entered-1;i++)
		printf("%d ",*(numbers+i));
	return 0;
}
