#include <stdio.h>
#include <stdlib.h>//use for functions atoi
#include <string.h>//use for functions strlen 
#include <math.h>//use for functions pow
//compilar as gcc file.c -lm
#define sizeofBinaryString 11 
char isBinaryString(char *string){
	int i,size=strlen(string);
	for(i=0;i<size;i++){
		if(string[i]!='0'&&string[i]!='1')
			return 0;
	}
	return 1;
}
int binaryToDecimal(char *binaryString){
	if(!isBinaryString(binaryString)){
		printf("please enter a number binary this just containts 0 and 1\ntry again\n");
		return -1;
	}
	int i,potencia,decimal=0,size=strlen(binaryString);
	char aux;
	for(i=size-1,potencia=0;i>=0;i--,potencia++){
		aux=binaryString[i];
		decimal+=atoi(&aux)*pow(2,potencia);
	}
	return decimal;
}
int main(){
	char binaryString[sizeofBinaryString];
	int decimal;
	printf("enter binary number\n");
	fgets(binaryString,sizeofBinaryString,stdin);
	binaryString[strlen(binaryString)-1]=0;
	if(!isBinaryString(binaryString)){
		printf("please enter a number binary this just containts 0 and 1\ntry again\n");
		return -1;
	}
	decimal=binaryToDecimal(binaryString);
	printf("%s (binary)=%d (decimal)\n",binaryString,decimal);
	return 0;
}
