#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define salaryWeek 200
#define percentWeek 9
char wasInThisRanger(int number,int limitDown,int limitUp){
	if(number>=limitDown&&number<=limitUp)
		return 1;
	return 0;
}
void printAmount(int *fullSalary,int size){
	int i,amount,limitDown,limitUp;
	for(limitDown=200,limitUp=limitDown+99;limitDown<=1000;limitDown+=100,amount=0){
		if((limitUp=limitDown+99)==1099)
			limitUp=2147483647;
		for(i=0;i<size;i++){
			if(wasInThisRanger(*(fullSalary+i),limitDown,limitUp))
				amount++;
		}
		if(limitDown==1000)
			printf("%d employer was in ranger $%d-superior\n",amount,limitDown);
		else
			printf("%d employer was in ranger $%d-$%d\n",amount,limitDown,limitUp);
	}
}
int main(){
	float bruteSale;
	int entered=1,*fullSalary=(int*)malloc(sizeof(int));
	char option[3];
	do{
		printf("would you like insert other brute sale? yes/not\n");
		scanf("%s",option);
		if(strncasecmp(option,"y",1))
			continue;
		printf("enter brute sales\n");
		scanf("%f",&bruteSale);
		*(fullSalary+entered-1)=(int)(salaryWeek+(bruteSale*percentWeek/100));
		printf("fullSalary for this employer=%d\n",*(fullSalary+entered-1));
		entered++;
		fullSalary=(int*)realloc(fullSalary,(sizeof(int)*entered));
	}while(strncasecmp(option,"n",1));
	printAmount(fullSalary,entered-1);
	return 0;
}
