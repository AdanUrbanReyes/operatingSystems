#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char multiple(int *first,int *second){
	if(*first%*second)
		return 1;
	return 0;
}
int main(){
	int *first=(int*)malloc(sizeof(int)),*second=(int*)malloc(sizeof(int));
	char *option=(char *)malloc(sizeof(char)*3);
	do{
		printf("would you like insert other brute sale? yes/not\n");
		scanf("%s",option);
		if(strncasecmp(option,"y",1))
			continue;
		printf("enter first number\n");
		scanf("%d",first);
		printf("enter second number\n");
		scanf("%d",second);
		if(multiple(first,second))
			printf("%d is multiple of %d\n",*second,*first);
		else
			printf("%d not is multiple of %d\n",*second,*first);
	}while(strncasecmp(option,"n",1));
	return 0;
}
