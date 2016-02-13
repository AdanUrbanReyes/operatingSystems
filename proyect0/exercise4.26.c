#include <stdio.h>
#include <unistd.h>
#define maxIteraciones 144839
/*
	3.14 en el termino 119
	3.141 en el termino 1688
	3.1415 en el termino 10742
	3.14159 en el terminino 144839
*/
int main(){
	double pi=0,div;
	int number,iteracion;//iteracion just increment wen number is impar and number increment always
	char signo=1;
	for(number=1,iteracion=0;iteracion<=maxIteraciones;number++){
		if(number%2){
			div=(float)4/number;
			div=div*signo;
			pi+=div;
			signo=signo-signo*2;
			iteracion++;
			printf("pi=%f a %d iteracion\n",pi,iteracion);
		}
	}
	return 0;
}
