#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int ari,char **arc){//execute as ./nameExecutable bytesToWrite
	int size=atoi(arc[1]);
	int descriptorFile,writed=0;
	char *buffer=(char *)malloc(sizeof(char)*size);
	while(writed<size){
		buffer[writed++]='$';
	}
	descriptorFile=open("file.txt",O_WRONLY|O_CREAT,0666);
	write(descriptorFile,buffer,size);
	sync();
	close(descriptorFile);
	return 0;
}
