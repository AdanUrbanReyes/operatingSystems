#include <stdio.h>
#include <stdlib.h>
/*
	
*/
int main(int ari,char **arc){
	char *info=getenv(arc[1]);
	printf("getenv(%s)=\n\t%s\n",arc[1],info);
	return 0;
}
