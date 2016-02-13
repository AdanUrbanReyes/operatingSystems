#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define digits 5
int main(){
	int i,number,digitsInNumber=0;
	char *string=(char *)malloc(sizeof(char)*digits);
	printf("enter number\n");
	scanf("%d",&number);
	sprintf(string,"%d",number);
	digitsInNumber=strlen(string);
	for(i=0;i<digitsInNumber;i++){
		printf("%c	",string[i]);
	}
	return 0;
}
