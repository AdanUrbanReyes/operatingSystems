#include <stdio.h>
#include <stdlib.h>
int main(int ari,char **arc){
	int token;
	for(token=0;token<ari;token++){
		if(arc[token][0]=='-')
			printf("option: %s\n",arc[token]+1);
		else
			printf("argumento %d: %s\n",token,arc[token]);
	}
	return 0;
}
