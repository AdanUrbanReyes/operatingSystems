/*
   this program estima constant e utilizando formula
   e=1+1/1!+1/2!+1/3!+...
*/
#include <stdio.h>
double factorial(unsigned char number){
   double factorial=1;
   while(number>=1){
      factorial*=number--;
   }
   return factorial;
}
double getEulerNumber(){
	double eulerNumber=0;
	unsigned char number=0;
	while(number<170)
		eulerNumber+=1/factorial(number++);
	return eulerNumber;
}
int main(){
	printf("number euler=%g\n",getEulerNumber());	
	return 0;
}
