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
#include <sys/sem.h>
#include <unistd.h>

void printStructSembuf(struct sembuf *operacion){
	printf("sem_num=%d\n",operacion->sem_num);
	printf("sem_op=%d\n",operacion->sem_op);
	printf("sem_flg=%d\n",operacion->sem_flg);
}
int main(int ari,char **arc){
	int semid,j=10;
	struct sembuf operacion;
	key_t llave;
	//printStructSembuf(&operacion);
	llave=ftok(arc[0],7);
	if((semid=semget(llave,3,IPC_CREAT|0600))==-1){
		perror("error al ejecutar semget\n");
		exit(-1);
	}
	semctl(semid,0,SETVAL,1);//pone el semafor del padre en 1 verde
	semctl(semid,1,SETVAL,0);//pone el hijo "terminal hija1" en 0
	semctl(semid,2,SETVAL,0);//pone el hijo "terminal hija2" en 0
	while(j){
		/*se realiza la operacion down en el semaforo del proceso hijo*/
		operacion.sem_flg=0;
		operacion.sem_op=-1;//operacion down
		operacion.sem_num=0;//down al padre
		semop(semid,&operacion,1);
		printf("soy el proceso %d. impresion: %d\n",getpid(),j--);
		/*se realiza la operacion up en el semaforo del proceso padre*/
		operacion.sem_op=1;
		operacion.sem_num=1;
		semop(semid,&operacion,1);
	}
	/*borramos el semaforo*/
	semctl(semid,0,IPC_RMID,0);
	return 0;
}
