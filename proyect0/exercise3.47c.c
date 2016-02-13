/*
	this program estima constant e utilizando formula
	e=1+x/1!+x^2/2!+x^3/3!+...
*/
#include <stdio.h>
#include <math.h>
//compilar as gcc file.c -lm
double factorial(unsigned char number){
	double factorial=1;
	while(number>=1){
		factorial*=number--;
	}
	return factorial;
}
double getEulerNumber(float potencia){
	double eulerNumber=0;
	unsigned char number=0;
	while((number++)<170)
		eulerNumber+=(pow(potencia,number-1)/factorial(number-1));
	return eulerNumber;
}
int main(){
	float potencia;
	printf("i calculator e^x\nplese enter value of x\n");	
	scanf("%f",&potencia);
	printf("e^%g=%g\n",potencia,getEulerNumber(potencia));
	return 0;
}

