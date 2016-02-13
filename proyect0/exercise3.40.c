#include <stdio.h>
#include <stdlib.h>
#define rows 8
#define columns 8
int main(){
	int i;
	char *string=(char*)malloc(sizeof(char)*(columns*2));
	for(i=0;i<columns*2;i+=2){
		string[i]='*';
		string[i+1]=' ';
	}
	for(i=1;i<=rows;i++){
		if(i%2){
			printf(" ");
		}
		printf("%s\n",string);
	}
	return 0;
}
