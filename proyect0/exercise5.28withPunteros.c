#include <stdio.h>
#include <string.h>//for use functions strlen
#include <stdlib.h>
int *invertInteger(int *number){
	int *invertido,*i,*j;
	invertido=(int*)malloc(sizeof(int));
	i=(int*)malloc(sizeof(int));
	j=(int*)malloc(sizeof(int));
	char *aux,*temp;
	aux=(char*)malloc(sizeof(char)*11);
	temp=(char*)malloc(sizeof(char)*11);
	bzero(temp,11);
	sprintf(aux,"%d",*number);
	for(*i=strlen(aux)-1,*j=0;*i>=0;*i=*i-1,*j=*j+1)
		temp[*j]=aux[*i];
	sscanf(temp,"%d",invertido);
	return invertido;
}
int main(){
	int *number=(int*)malloc(sizeof(int));
	printf("enter a number\n");
	scanf("%d",number);
	printf("%d inverter %d\n",*number,*invertInteger(number));
	return 0;
}
