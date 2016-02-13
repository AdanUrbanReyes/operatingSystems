#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
	int entero = 0;
	float flotante = 0;
	char caracter = 0;
	long largo = 0;
	double doble = 0;
	int negativoPositivo;
	char *cadena={"ESCOM - IPN"};
	char *pcaracter={"h"};
	int *pentero=(int *)malloc(sizeof(int));
	*pentero=1;
	float *pflotante=(float *)malloc(sizeof(float));
	*pflotante=7.1;
	long *plargo=(long *)malloc(sizeof(long));
	*plargo=11;
	double *pdouble=(double *)malloc(sizeof(double));
	*pdouble=3.71;
	printf("sizeof(char) = %ld\n",sizeof(char));
	printf("sizeof(int) = %ld\n",sizeof(int));
	printf("sizeof(floatante) = %ld\n",sizeof(float));
	printf("sizeof (largo)= %ld\n",sizeof(long));
	printf("sizeof(double) %ld\n",sizeof(double));
	printf("char      = %p\n",&caracter);
	printf("int       = %p\n",&entero);
	printf("floatante = %p\n",&flotante);
	printf("largo     = %p\n",&largo);
	printf("double    = %p\n",&doble);
	printf("char      = %ld\n",(long int)&caracter);
	printf("int       = %ld\n",(long int)&entero);
	printf("floatante = %ld\n",(long int)&flotante);
	printf("largo     = %ld\n",(long int)&largo);
	printf("double    = %ld\n",(long int)&doble);
	printf("char      = %ld\n",sizeof(&caracter));
	printf("int       = %ld\n",sizeof(&entero));
	printf("floatante = %ld\n",sizeof(&flotante));
	printf("largo     = %ld\n",sizeof(&largo));
	printf("double    = %ld\n",sizeof(&doble));
	printf("*char      = %ld/%c\n",sizeof(pcaracter),*pcaracter);
	printf("*int       = %ld/%d\n",sizeof(pentero),*pentero);
	printf("*floatante = %ld/%f\n",sizeof(pflotante),*pflotante);
	printf("*largo     = %ld/%ld\n",sizeof(plargo),*plargo);
	printf("*double    = %ld/%f\n",sizeof(pdouble),*pdouble);
	printf("cadena+4=%c\n",*(cadena+4));
	if(cadena[strlen(cadena)]=='\0'){
		printf("fin de linea para cadena\n");
	}
	negativoPositivo=2147483649;
	printf("negativoPositivo=%d\n",negativoPositivo);
	return 0;
}
