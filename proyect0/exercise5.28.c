#include <stdio.h>
#include <string.h>//for use functions strlen
int invertInteger(int number){
	int invertido,i,j;
	char aux[11],temp[11];
	bzero(temp,11);
	sprintf(aux,"%d",number);
	for(i=strlen(aux)-1,j=0;i>=0;i--,j++)
		temp[j]=aux[i];
	sscanf(temp,"%d",&invertido);
	return invertido;
}
int main(){
	int number;
	printf("enter a number\n");
	scanf("%d",&number);
	printf("%d inverter %d\n",number,invertInteger(number));
	return 0;
}
