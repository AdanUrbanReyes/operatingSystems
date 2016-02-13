#include <stdio.h>
#include <math.h>
#define PI 3.14159
//compilar as gcc file.c -lm
int main(){
	float radius;
	printf("enter circle radius\n");
	scanf("%f",&radius);
	printf("circle diameter is %f\n",radius*2);
	printf("circle circunference is %f\n",PI*radius);
	printf("circle area is %f\n",PI*pow(radius,2));
	return 0;
}
