#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int ari,char **arc){//execute as ./nameExecutable bytesToWrite pathUSB
   int size=atoi(arc[1]);
   int descriptorFile,writed=0;
	char *pathUSB=arc[2],character='a';
   if((descriptorFile=open(pathUSB,O_WRONLY|O_CREAT,0666))==-1){
		printf("error open file %s\n",pathUSB);
		return -1;
	}
   while((writed++)<size){
   	write(descriptorFile,&character,sizeof(char));
   }
   sync();
   close(descriptorFile);
	return 0;
}
