/* Programa que ilustra el uso de semaforos*/
/*
		que valores iniciales tiene la variable operaciones (struct sembuf)?
			r= tiene basura
		cuando se modifican sus valores que funcion ase uso de dichas variables?
			r= la funcion semop
		continua funcionando si declaro 5 semaforos en la linea semget?
			r=si
		que ocurre si se inicializan los semaforos en 0?
			
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SEMAFORO_PADRE 1
#define SEMAFORO_HIJO 0
void printStructSembuf(struct sembuf *operacion){
	printf("sem_num=%d\n",operacion->sem_num);
	printf("sem_op=%d\n",operacion->sem_op);
	printf("sem_flg=%d\n",operacion->sem_flg);
}
int main(int ari,char **arc){
	int semid,pid;
	int *number,idSharedMemoryNumber,iteraciones,i;
	struct sembuf operacion;
	key_t llave,keySharedNumber;
	keySharedNumber=ftok("/bin/ls",7);
	idSharedMemoryNumber=shmget(keySharedNumber,sizeof(int),IPC_CREAT|0600);
	number=(int *)shmat(idSharedMemoryNumber,NULL,0);
	*number=0;
	iteraciones=atoi(arc[1]);
	//printStructSembuf(&operacion);
	llave=ftok(arc[0],'U');
	if((semid=semget(llave,5,IPC_CREAT|0600))==-1){
		perror("error al ejecutar semget\n");
		exit(-1);
	}
	semctl(semid,SEMAFORO_HIJO,SETVAL,0);
	semctl(semid,SEMAFORO_PADRE,SETVAL,1);
	/*se crea el proceso hijo*/
	if((pid=fork())==-1){
		perror("error al ejecutar fork\n");
		exit(-1);
	}else if(pid==0){
		/*codigo correspondiente al proceso hijo*/
		for(i=0;i<iteraciones;i++){
			/*se realiza la operacion down en el semaforo del proceso hijo*/
			operacion.sem_flg=0;
			operacion.sem_op=-1;
			operacion.sem_num=SEMAFORO_HIJO;
			semop(semid,&operacion,1);
			(*number)--;
	//		printf("soy el proceso hijo. impresion: %d\n",*number);
			/*se realiza la operacion up en el semaforo del proceso padre*/
			operacion.sem_op=1;
			operacion.sem_num=SEMAFORO_PADRE;
			semop(semid,&operacion,1);
		}
		/*borramos el semaforo*/
		semctl(semid,0,IPC_RMID,0);
	}else{
		/*codico correspondiente al proceso padre*/
		for(i=0;i<iteraciones;i++){
			/*se realiza la operacion down en el semaforo del proceso padre*/
			operacion.sem_flg=0;
			operacion.sem_op=-1;
			operacion.sem_num=SEMAFORO_PADRE;
			semop(semid,&operacion,1);
			(*number)++;
	//		printf("soy el proceso padre. impresion: %d\n",*number);
			/*se realiza la operacion up en el semaforo del proceso hijo*/
			operacion.sem_op=1;
			operacion.sem_num=SEMAFORO_HIJO;
			semop(semid,&operacion,1);
		}
		/*borramos el semaforo*/
		semctl(semid,0,IPC_RMID,0)	;
		return 0;
	}
	printf("number=%d\n",*number);
	semctl(idSharedMemoryNumber,0,IPC_RMID,0);
	return 0;
}
