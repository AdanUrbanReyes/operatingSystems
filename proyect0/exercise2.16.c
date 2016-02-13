#include <stdio.h>
int main(){
	float oneNumber,twoNumber;
	printf("enter two numbers\n");
	scanf("%f",&oneNumber);
	scanf("%f",&twoNumber);
	printf("%g+%g=%g\n",oneNumber,twoNumber,(oneNumber+twoNumber));
	printf("%g-%g=%g\n",oneNumber,twoNumber,(oneNumber-twoNumber));
	printf("%g-%g=%g\n",twoNumber,oneNumber,(twoNumber-oneNumber));
	printf("%g*%g=%g\n",oneNumber,twoNumber,(oneNumber*twoNumber));
	printf("%g/%g=%g\n",oneNumber,twoNumber,(oneNumber/twoNumber));
	printf("%g/%g=%g\n",twoNumber,oneNumber,(twoNumber/oneNumber));
	printf("%d %% %d=%d\n",(int)oneNumber,(int)twoNumber,(int)oneNumber%(int)twoNumber);
	printf("%d %% %d=%d\n",(int)twoNumber,(int)oneNumber,(int)twoNumber%(int)oneNumber);
	return 0;
}
