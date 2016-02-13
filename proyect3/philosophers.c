#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <time.h>

#define PHILOSOPHER 5 //número de filósofos 
#define LEFT (i+PHILOSOPHER-1)%PHILOSOPHER //número del vecino izquierdo de i 
#define RIGHT (i+1)%PHILOSOPHER //número del vecino derecho de i 
#define THINKING 0 //el filósofo está pensando 
#define HUNGRY 1 //el filósofo trata de obtener los tenedores 
#define EATING 2 //el filósofo está comiendo 

typedef struct SharedMemory{
	key_t key;
	int id;
	void *memory;
}SharedMemory;
typedef struct Semaphore{
	key_t key;
	int id;
	struct sembuf operation;
}Semaphore;
/*
typedef int semaforo; //los semáforos son un tipo especial de int 
int estado[PHILOSOPHER]; //arreglo que lleva registro del estado de todos
semaforo mutex = 1; //exclusión mutua para las regiones críticas 
semaforo s[PHILOSOPHER]; //un semáforo por filósofo 
*/
SharedMemory shared;
Semaphore semaphore;
void executeOperationSemaphore(int numberSemaphore,int operation){
	semaphore.operation.sem_num=numberSemaphore;
	semaphore.operation.sem_op=operation;
	semaphore.operation.sem_flg=0;
	semop(semaphore.id,&semaphore.operation,1);
}
void eat(){
	long int seconds=(random()%3)+3;
	system("clear");
	printf("eating by %ld seconds\n",seconds);
	sleep(seconds);
}
void thing(){
	long int seconds=(random()%3)+1;
	system("clear");
	printf("thinking by %ld seconds\n",seconds);
	sleep(seconds);
}
void test(int i){ //i: número de filósofo, de 0 a PHILOSOPHER-1 
	if (((int*)shared.memory)[i] == HUNGRY && ((int *)shared.memory)[LEFT] != EATING && ((int *)shared.memory)[RIGHT] != EATING) {
		((int *)shared.memory)[i] = EATING;
		executeOperationSemaphore(i,1);
	}
}
void takeForks(int i){ // i: número de filósofo, de 0 a PHILOSOPHER-1  
	executeOperationSemaphore(5,-1);//down(&mutex); //entra a la región crítica 
	((int *)shared.memory)[i]=HUNGRY;//estado[i] = HAMBRIENTO; //registra el hecho de que el filósofo i está hambriento 
	system("clear");
	printf("hungry...\n");
	test(i); //trata de adquirir 2 tenedores 
	executeOperationSemaphore(5,1);//up(&mutex); //sale de la región crítica 
	executeOperationSemaphore(i,-1);//down(&s[i]); //se bloquea si no se adquirieron los tenedores 
} 
void setForks(int i){// i: número de filósofo, de 0 a PHILOSOPHER–1 
	executeOperationSemaphore(5,-1);//down(&mutex);	//entra a la región crítica 
	((int *)shared.memory)[i]=THINKING;//estado[i] = PENSANDO;//el filósofo terminó de comer 
	test(LEFT);//probar(IZQUIERDO);//verifica si el vecino izquierdo puede comer ahora 
	test(RIGHT);//probar(DERECHO);//verifica si el vecino derecho puede comer ahora 
	executeOperationSemaphore(5,1);//up(&mutex);//sale de la región crítica 
}
void philosopher(int i){ // i: número de filósofo, de 0 a PHILOSOPHER-1  
	while(1){ //se repite en forma indefinida 
		thing(); //el filósofo está pensando 
		takeForks(i); //adquiere dos tenedores o se bloquea 
		eat(); //come espagueti 
		setForks(i); //pone de vuelta ambos tenedores en la mesa 
	}
}
Semaphore createSemaphore(char *path,char id,int semaphores){
	Semaphore semaphore;
	semaphore.key=ftok(path,id);
	if(semaphore.key==-1){
		printf("error getting key (ftok function error)\n");
		exit(-1);
	}
	semaphore.id=semget(semaphore.key,semaphores,IPC_CREAT | 0644);
	if(semaphore.id==-1){
		printf("error getting id of semaphore memory (shmget function error)\n");
		exit(-1);
	}
	return semaphore;
}
SharedMemory createSharedMemory(char *path,char id,size_t memory){
	SharedMemory shared;
	shared.key=ftok(path,id);
	if(shared.key==-1){
		printf("error getting key (ftok function error)\n");
		exit(-1);
	}
	shared.id=shmget(shared.key,memory,IPC_CREAT | 0644);
	if(shared.id==-1){
		printf("error getting id of semaphore memory (shmget function error)\n");
		exit(-1);
	}
	shared.memory=shmat(shared.id,NULL,0);
	if(shared.memory==NULL){
		printf("error getting memory (shmat function error)\n");
		exit(-1);
	}
	return shared;
}
void startSharedMemory(int tope,int value){
	int i;
	for(i=0;i<tope;i++){
		((int*)shared.memory)[i]=value;
	}
}
void startSemaphores(int id,int semaphores){
	int i;
	for(i=0;i<semaphores-1;i++){
		semctl(id,i,SETVAL,0);
	}
}
void endSemaphores(int id,int semaphores){
	int i;
	for(i=0;i<semaphores;i++){
		semctl(id,i,IPC_RMID,0);
	}
}
int main(int ari,char **arc){
	if(ari<2){
		printf("error please execute as %s numberPhilosopher\nNOTE: numberPhilosopher has values of 0 to 4\n",arc[0]);
		return 0;
	}
	if(arc[1][0]=='c'){
		shmctl(shared.id,IPC_RMID,0);
		endSemaphores(semaphore.id,6);	
		printf("memory cleaned\n");
		return 0;
	}
	int philosopherNumber=atoi(arc[1])-1;
	if(philosopherNumber>4||philosopherNumber<0){
		printf("error philosopher is the 1 to 5\n");
		return -1;
	}
	srand(time(NULL));
	shared=createSharedMemory("/bin/ls",11,sizeof(int)*PHILOSOPHER);
	semaphore=createSemaphore("/bin/ls",7,PHILOSOPHER+1);
	if(philosopherNumber==0){
		startSharedMemory(5,0);
		semctl(semaphore.id,5,SETVAL,1);
		startSemaphores(semaphore.id,6);
	}
	philosopher(philosopherNumber);
	shmctl(shared.id,IPC_RMID,0);
	endSemaphores(semaphore.id,6);
	return 0;
}
