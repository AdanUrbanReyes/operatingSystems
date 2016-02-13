#include <stdio.h>
#include <stdlib.h>//for use functions realloc
#include <string.h>
char even(int number){
	if(!(number%2))
		return 1;
	return 0;
}
int main(){
	int *numbers,i,numbersEntered=1;
   char option[3];
	do{
     	printf("would you like insert other brute sale? yes/not\n");
      scanf("%s",option);
      if(strncasecmp(option,"y",1))
         continue;
		numbers=(int*)realloc(numbers,sizeof(int)*numbersEntered);
		printf("enter number\n");
		scanf("%d",(numbers+numbersEntered-1));
		numbersEntered++;
   }while(strncasecmp(option,"n",1));
	for(i=0;i<numbersEntered-1;i++){
		if(even(*(numbers+i)))
			printf("%d is par\n",*(numbers+i));
		else
			printf("%d is impar\n",*(numbers+i));
	}
	return 0;
}
