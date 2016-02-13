#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#define iteraciones 7
int main(){
	int i;
	struct sembuf operation;
	pid_t pid;
	key_t key=ftok("/bin/ls",7);
	int idSemaforo=semget(key,1,IPC_CREAT|0600);
	semctl(idSemaforo,0,SETVAL,1);
	pid=fork();
	switch(pid){
		case -1:
			printf("error create process\n");
		break;
		case 0:
			for(i=0;i<iteraciones;i++){
				operation.sem_num=0;
				operation.sem_op=-1;
				operation.sem_flg=0;	
				semop(idSemaforo,&operation,0);
				printf("ping\n");
				operation.sem_num=0;
				operation.sem_op=1;
				operation.sem_flg=0;	
				semop(idSemaforo,&operation,0);
			}
			semctl(idSemaforo,0,IPC_RMID,0);
			return 0;
		break;
		default:
			for(i=0;i<iteraciones;i++){
				operation.sem_num=0;
				operation.sem_op=-1;
				operation.sem_flg=0;	
				semop(idSemaforo,&operation,0);
				printf("pong\n");
				operation.sem_num=0;
				operation.sem_op=1;
				operation.sem_flg=0;	
				semop(idSemaforo,&operation,0);
			}
	}
	wait(NULL);
	semctl(idSemaforo,0,IPC_RMID,0);
	return 0;
}
