#include <stdio.h>
int main(){
	int tanks=0;
	float miles,gallon,milesByGallon=0,average=0;
	do{
		printf("\nEnter the gallons used (-1 to end): ");
		scanf("%f",&gallon);
		if(gallon==-1)
			continue;
		printf("\nEnter the miles driven: ");
		scanf("%f",&miles);
		milesByGallon=miles/gallon;
		average+=milesByGallon;
		tanks++;
		printf("The miles / gallon for this tank was %f\n",milesByGallon);
	}while(gallon!=-1);
	average/=tanks;
	printf("The overall average miles/gallon was %f",average);
	return 0;
}
