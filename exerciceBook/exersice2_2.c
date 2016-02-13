#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int ari,char **arc){
	int token;
	for(token=0;token<ari;token++){
		if(arc[token][0]=='-')
			printf("option: %s\n",arc[token]+1);
		else
			printf("argumento %d: %s/%d\n",token,arc[token],(int)strlen(arc[token]));
	}
	return 0;
}
