#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	int i=0,state;
	pid=fork();
	if(pid==0){
		sleep(1);
		printf("i am son: pid:%d father pid:%d i:%d\n",getpid(),getppid(),++i);
		exit(3);
		/*
			 1 00000000	
			10 00000000
         11 00000000
		*/
	}else{
		if(pid>0){
			printf("i am father: pid:%d father pid:%d i:%d\n",getpid(),getppid(),++i);	
			wait(&state);
			state>>=8;
		printf("my son finish with code %d\n",state);	
		}
	}
	return 0;
}
