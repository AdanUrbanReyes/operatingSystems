#include <stdio.h>
/*
	cuando se ejecuta este programa 
	se imprimen los multiplos de dos hazta que el multiplo sea menor que el numero maximo que cabe en el tipo de variable
	una vez alcanzado este numero imprimira puros ceros
	ejemplo en este programa se usa una variable de tipo int para almacenar el multiplo
	savemos que un int en linux ocupa 4 bytes entonces el numero mas grande a almacenar es 2^32-1 
	una ves que el multiplo revace 2^32-1 imprimira puros 0
*/
int main(){
	int multiplo=2;
	while(1){
		printf("%d ",multiplo);
		multiplo*=2;
	}
	return 0;
}
