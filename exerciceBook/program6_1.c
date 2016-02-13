#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
key_t getKey(char *path,int value){
	key_t=ftok(path,value);//path route a file existing and unico , value cualquier valor
	if(key_t==-1){
		printf("error getting key %d\n",EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
	return key_t;
}
int getIdMemoryShare(key_t key,){
	
}
int main(int ari,char **arc){
	int *
	key_t keyStock=ftok(arc[0],11),keyTope=(arc[0],7);
	
	return 0;
}
