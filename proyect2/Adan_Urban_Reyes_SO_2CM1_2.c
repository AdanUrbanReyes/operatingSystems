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
#define lenghtFile 100
/*
	struct dirent on man readdir
*/
int process=7;
char *path;
typedef struct fileData{
	char name[lenghtFile];
	struct fileData *next;
}fileData;
typedef struct workProcess{
	pid_t pid;
	char nameFile[lenghtFile];
	int matches;
	int flat;
}workProcess;
typedef struct sharedMemory{
	key_t key;
	int id;
	void *memory;
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
long sizeofFile(char *fileName){
	unsigned int lenghtPathDirectory=strlen(path);
	unsigned int lenghtNameFile=strlen(fileName);//get lenght name file
	char *pathFile=(char *)malloc(sizeof(char)*(lenghtPathDirectory+lenghtNameFile));//recervo memory for path complet (path directory+name file)
	strcpy(pathFile,path);//copy path to full path
	strcat(pathFile,fileName);//concateno name file with fullPath then fullPath containts route complete 
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
			printf("name=%s\n",head->name);
			head=head->next;
		}
}
void addFileData(fileData **head,char *name){
	fileData *temp=(fileData *)malloc(sizeof(fileData));
	strcpy(temp->name,name);
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
	unsigned int files=0;
	fileData *head=NULL;
	if((directory=opendir(pathDirectory))==NULL){//open directory
		printf("error open directory %s\n",pathDirectory);
		exit(-1);
	}
	while((file=readdir(directory))!=NULL){//start read all files to this directory
		if((!strcmp(file->d_name,"."))||(!strcmp(file->d_name,"..")))//if file is . (directory actual) or file is .. (directory father) dont import
			continue;
		addFileData(&head,file->d_name);//add to list this file sending name and size 
		//printf("route=|%s|\n",fullPath);
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
void distributeFiles(fileData *head,fileData ***headsPointer){
	fileData **heads=*headsPointer;
	long double totalBytes[process];
	int i,im;
	double menor=1073741824;
	for(i=0;i<process;i++,head=head->next){//first fill all array dataProcess with a file
		heads[i]=NULL;
		totalBytes[i]=sizeofFile(head->name);//start totalBytes with size file puted
		addFileData(&heads[i],head->name);//add file to list that dataProcess
	}
	while(head!=NULL){//set all files restantes in array dataProcess
		for(i=0;i<process;i++){//search process with "menos work"
			if(totalBytes[i]<menor){
				menor=totalBytes[i];
				im=i;
			}
		}
		totalBytes[im]+=sizeofFile(head->name);//aumento totalBytes 
		menor=totalBytes[im];
		addFileData(&(heads[im]),head->name);//add file to list that dataProcess
		head=head->next;//recorro one position pointer
	}
	/*for(i=0;i<process;i++){
		printf("process %d-%Lf\n",i,totalBytes[i]);
		printListFileData(heads[i]);
		printf("\n");
	}*/
}
int numberFilesByProcess(fileData *head){
	int files=0;
	while(head!=NULL){
		files++;
		head=head->next;
	}
	return files;
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
   shared.memory=shmat(shared.id,NULL,0);
   if(shared.memory==NULL){
      printf("error gettin memory shared (shmat function error)\n");
      exit(-1);
   }
   return shared;
}
void fillSharedMemoryFileData(fileData *list,void **memory){
	fileData *head=(fileData*)*memory;
	int i=0;
	while(list!=NULL){
		strcpy(head[i].name,list->name);
		if(list->next==NULL){
			head[i].next=NULL;
		}else{
			head[i].next=&head[i+1];
		}
		list=list->next;
		i++;
	}
}
int searchCharacter(char *fileName,char character){
	unsigned int lenghtPathDirectory=strlen(path);
	unsigned int lenghtNameFile=strlen(fileName);//get lenght name file
	char *pathFile=(char *)malloc(sizeof(char)*(lenghtPathDirectory+lenghtNameFile));//recervo memory for path complet (path directory+name file)
	strcpy(pathFile,path);//copy path to full path
	strcat(pathFile,fileName);//concateno name file with fullPath then fullPath containts route complete 
   int descriptor=open(pathFile,O_RDONLY);
	int matches=0;
   char buffer;
   if(descriptor==-1){
      printf("error opening file %s (open function error)\n",pathFile);
      exit(-1);
   }
   while(read(descriptor,&buffer,sizeof(char))!=0){
      if(buffer==character)
         matches++;
   }
	close(descriptor);
	return matches;
}
void createProcess(int fakePid,char character,size_t memory){
   pid_t pid=fork();
	fileData *list;
   workProcess *wp=(workProcess *)createSharedMemory("/bin/ls",7+fakePid,sizeof(workProcess)).memory;
	wp->pid=getpid();
   switch(pid){
      case -1:
         printf("error creating process (fork function error)\n");
      break;
      case 0:
         list=(fileData *)createSharedMemory("/bin/ls",fakePid,memory).memory;
         while(list!=NULL){
				wp->matches=searchCharacter(list->name,character);
				strcpy(wp->nameFile,list->name);
				wp->flat=1;
				while(wp->flat!=2){;}
				list=list->next;
         }
			wp->flat=0;
         exit(0);
      break;
   }
}
int main(int ari,char **arc){
	if(ari<3){
		printf("error please execute as %s pathDirectory characterToSearch\n",arc[0]);
		return 0;
	}
	path=arc[1];//set path in global variable
	fileData *head=NULL;//lista all files that directory with name,size,matches and *next
	head=readFilesDirectory(arc[1]);
	//printListFileData(head);
	fileData **heads=(fileData **)malloc(sizeof(fileData *)*process);
	distributeFiles(head,&heads);
	int i;
	size_t memoryToRecerver;
	sharedMemory shared[process];
	sharedMemory shared2[process];
	for(i=0;i<process;i++){
      shared2[i]=createSharedMemory("/bin/ls",7+i,sizeof(workProcess));
		((workProcess *)shared2[i].memory)->flat=2;
	}
	for(i=0;i<process;i++){
		memoryToRecerver=sizeof(fileData)*numberFilesByProcess(heads[i]);
      shared[i]=createSharedMemory("/bin/ls",i,memoryToRecerver);
		fillSharedMemoryFileData(heads[i],&shared[i].memory);
		createProcess(i,arc[2][0],memoryToRecerver);
		//sleep(i+1);
	}
	printf("Proceso padre PID = %d\n",getpid());
   char aux[50];
   printWithFormatString("ARCHIVO",40);
   printWithFormatString("PID",11);
   sprintf(aux,"NO. CARACTERES '%c' ENCONTRADOS",arc[2][0]);
   printWithFormatString(aux,40);
   printf("\n");
	int suma=1;
	while(suma){
		for(i=0,suma=0;i<process;i++){
			workProcess *wp=(workProcess*)shared2[i].memory;
			if(wp->flat==1){//value one actualizado
				printWithFormatString(wp->nameFile,40);
   	      printWithFormatLong((long)wp->pid,11);
      	   printWithFormatLong((long)wp->matches,40);
				printf("\n");
				wp->flat=2;//value two leido
			}
			suma+=wp->flat;
		}
	}
	for(i=0;i<process;i++){
		wait(NULL);
	}
	for(i=0;i<process;i++){
    	/*fileData *list=(fileData *)shared[i].memory;
         while(list!=NULL){
				printf("father=%d\nfile=%s\n",getpid(),list->name);
				list=list->next;
         }*/
      shmdt((char *)shared2[i].memory);
      shmctl(shared2[i].id,IPC_RMID,(struct shmid_ds *)NULL); 
      shmdt((char *)shared[i].memory);
      shmctl(shared[i].id,IPC_RMID,(struct shmid_ds *)NULL); 
	}
	
	return 0;
}
