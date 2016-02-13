#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int ari,char **arc){
	int descriptor,invertido,i=-2;
	char *buffer=(char *)malloc(sizeof(char));
	invertido=open(arc[2],O_WRONLY|O_CREAT|O_TRUNC,0600);
	descriptor=open(arc[1],O_RDONLY);
	while(lseek(descriptor,i,SEEK_END)!=-1){
		read(descriptor,buffer,sizeof(char));
		write(invertido,buffer,sizeof(char));
		i--;
	}
	return 0;
}
