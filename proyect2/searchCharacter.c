#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
/*
	struct dirent on man readdir
*/
int process=7;
typedef struct fileData{
	char *name;
	long size;
	int matches;
	struct fileData *next;
}fileData;
typedef struct dataWorkProcess{
	pid_t pid;
	struct fileData *head;
	double totalBytes;
}dataWorkProcess;
typedef struct sharedMemory{
	key_t key;
	int id;
	struct dataWorkProcess *dataProcess;
}sharedMemory;
void printWithFormatString(char *string,int tope){
	int i=tope-strlen(string);
	printf("%s",string);
	while((i--)>0)
		printf(" ");
}
void printWithFormatLong(long integer,int tope){
	char *string=(char *)malloc(sizeof(char)*20);
	sprintf(string,"%ld",integer);
	printWithFormatString(string,21);
}
long sizeofFile(char *pathFile){
	FILE *file=fopen(pathFile,"rb");//try open file
	if(file==NULL){//in case error
		printf("error opening file %s to calculator size\n",pathFile);
		exit(-2);
	}
	fseek(file,0,SEEK_END);//move strem (pointer) to end file
	long size=ftell(file);//get number bytes moved
	fclose(file);//close file
	return size;
}
void printListFileData(fileData *head){
		while(head!=NULL){
			printf("name=%s\t",head->name);
			printf("size=%ld\t",head->size);
			printf("matches=%d\n",head->matches);
			head=head->next;
		}
}
void printArrayDataWorkProcess(dataWorkProcess *dataProcess,int tope){
	int i;
	for(i=0;i<tope;i++){
		printf("pid=%d\n",dataProcess[i].pid);
		printListFileData(dataProcess[i].head);
		printf("totalBytes=%f\n\n",dataProcess[i].totalBytes);
	}
}
void addFileData(fileData **head,char *name,long size){
	fileData *temp=(fileData *)malloc(sizeof(fileData));
	temp->name=strdup(name);
	temp->size=size;
	temp->matches=0;
	temp->next=NULL;
	if(*head==NULL){
		*head=temp;
	}else{
		fileData *aux=*head;
		while(aux->next!=NULL){
			aux=aux->next;
		}
		aux->next=temp;	
	}
}
fileData *readFilesDirectory(char *pathDirectory){//function read directory, by cada file found lo add to list, de ser the case set number process
	DIR *directory;
	struct dirent *file;
	unsigned int files=0,lenghtNameFile,lenghtPathDirectory;
	lenghtPathDirectory=strlen(pathDirectory);
	char *fullPath=NULL;
	fileData *head=NULL;
	if((directory=opendir(pathDirectory))==NULL){//open directory
		printf("error open directory %s\n",pathDirectory);
		exit(-1);
	}
	while((file=readdir(directory))!=NULL){//start read all files to this directory
		if((!strcmp(file->d_name,"."))||(!strcmp(file->d_name,"..")))//if file is . (directory actual) or file is .. (directory father) dont import
			continue;
		lenghtNameFile=strlen(file->d_name);//get lenght name file
		fullPath=(char *)malloc(sizeof(char)*(lenghtPathDirectory+lenghtNameFile));//recervo memory for path complet (path directory+name file)
		strcpy(fullPath,pathDirectory);//copy path to full path
		strcat(fullPath,file->d_name);//concateno name file with fullPath then fullPath containts route complete 
		addFileData(&head,fullPath,sizeofFile(fullPath));//add to list this file sending name and size 
		//printf("route=|%s|\n",fullPath);
		bzero(fullPath,sizeof(char)*(lenghtPathDirectory+lenghtNameFile));//recervo memory for path complet (path directory+name file)
		fullPath=NULL;
		//free(fullPath);
		files++;//aumento file readed for this directory
	}
	if(closedir(directory)==-1){
		printf("error closing directory %s\n",pathDirectory);
	}
	if(files<process){//if number files that this directory is menor that number process then 
		process=files;//number process is same that number files (have not chiste open more process that files)
	}
	return head;
}
void distributeFiles(fileData **head,dataWorkProcess **dataProcess){
	fileData *aux=NULL;
	*dataProcess=(dataWorkProcess *)malloc(sizeof(dataWorkProcess)*process);
	bzero(*dataProcess,sizeof(dataWorkProcess)*process);
	int i,im;
	double menor=1073741824;
	for(aux=*head,i=0;i<process;i++,aux=aux->next){//first fill all array dataProcess with a file
		(*dataProcess)[i].pid=i;//set "pid" because pid real will put other process
		(*dataProcess)[i].totalBytes=aux->size;//start totalBytes with size file puted
		addFileData(&((*dataProcess)[i].head),aux->name,aux->size);//add file to list that dataProcess
	}
	while(aux!=NULL){//set all files restantes in array dataProcess
		for(i=0;i<process;i++){//search process with "menos work"
			if((*dataProcess)[i].totalBytes<menor){
				menor=(*dataProcess)[i].totalBytes;
				im=i;
			}
		}
		(*dataProcess)[im].totalBytes+=aux->size;//aumento totalBytes 
		menor=(*dataProcess)[im].totalBytes;
		addFileData(&((*dataProcess)[im].head),aux->name,aux->size);//add file to list that dataProcess
		aux=aux->next;//recorro one position pointer
	}
	
	printArrayDataWorkProcess(*dataProcess,process);	
}
sharedMemory createSharedMemory(char *path,char id,size_t memory){
	sharedMemory shared;
	shared.key=ftok(path,id);
	if(shared.key==-1){
		printf("error gettin key (ftok function error)\n");
		exit(-1);
	}
	shared.id=shmget(shared.key,memory,IPC_CREAT|0600);
	if(shared.id==-1){
		printf("error getting id shared memory (shmget function error)\n");
		exit(-1);
	}
	shared.dataProcess=(dataWorkProcess *)shmat(shared.id,NULL,0);
	if(shared.dataProcess==NULL){
		printf("error gettin memory shared (shmat function error)\n");
		exit(-1);
	}
	return shared;
}
void searchCharacter(fileData **head,char character){
	int descriptor=open((*head)->name,O_RDONLY);
	char buffer;
	if(descriptor==-1){
		printf("error opening file %s (open function error)\n",(*head)->name);
		exit(-1);
	}
	while(read(descriptor,&buffer,sizeof(char))!=0){
		if(buffer==character)
			(*head)->matches++;
	}
}
void createProcess(int fakePid,char character){
	pid_t pid=fork();
	dataWorkProcess *dataProcessShared;
	fileData *aux=NULL;
	switch(pid){
		case -1:
			printf("error creating process (fork function error)\n");
		break;
		case 0:
			dataProcessShared=createSharedMemory("/bin/ls",fakePid,sizeof(dataWorkProcess)).dataProcess;
			dataProcessShared[0].pid=getpid();
			aux=dataProcessShared[0].head;
			while(dataProcessShared[0].head!=NULL){
				searchCharacter(&dataProcessShared[0].head,character);
				dataProcessShared[0].head=dataProcessShared[0].head->next;
			}
			dataProcessShared[0].head=aux;
			printArrayDataWorkProcess(dataProcessShared,1);	
			exit(0);
		break;	
	}
}
int main(int ari,char **arc){
	if(ari<3){
		printf("error please execute as %s pathDirectory characterToSearch\n",arc[0]);
		return 0;
	}
	fileData *head=NULL;//lista all files that directory with name,size,matches and *next
	head=readFilesDirectory(arc[1]);	
	//printListFileData(head);
	dataWorkProcess *dataProcess=NULL;//array whit fileData, pid, totalBytes
	distributeFiles(&head,&dataProcess);
	//printArrayDataWorkProcess(dataProcess,process);	
/*	sharedMemory *shared=(sharedMemory *)malloc(sizeof(sharedMemory)*process);
	int i;
	for(i=0;i<process;i++){
		shared[i]=createSharedMemory("/bin/ls",i,sizeof(dataWorkProcess));
		*(shared[i].dataProcess)=dataProcess[i];
	}
	printf("Proceso padre PID = %d\n",getpid());
	for(i=0;i<process;i++){
		createProcess(i,arc[2][0]);
		sleep(i+1);
	}
	for(i=0;i<process;i++){
		wait(NULL);
	}
	char aux[50];
	printWithFormatString("ARCHIVO",40);
	printWithFormatString("PID",4);
	sprintf(aux,"NO. CARACTERES '%c' ENCONTRADOS",arc[2][0]);
	printWithFormatString(aux,40);
	printf("\n");
	//fileData *temp;
	for(i=0;i<process;i++){
	//	for(temp=shared[i].dataProcess[0].head;temp!=NULL;temp=temp->next){
			printWithFormatString(strrchr(temp->name,'/')+1,40);
			printWithFormatLong((long)shared[i].dataProcess[0].pid,4);
			printWithFormatLong((long)temp->matches,40);
			printf("\n");
		}
		shmdt((char *)shared[i].dataProcess);
		shmctl(shared[i].id,IPC_RMID,(struct shmid_ds *)NULL);	
	}*/
	return 0;
}
