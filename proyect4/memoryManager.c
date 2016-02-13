#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>
#include <pthread.h>
#include "list.h"
#include "graphics.h"
pthread_mutex_t mutex;
Node *head=NULL;//check this 
Node* bestFit(Node **head,unsigned short sizeProcess){//this function return pointer to best hollow or NULL if not find hollow
	Node *auxiliary=*head,*bestHollow=NULL;//pointer to best hollow
	unsigned short difference=65535;//diferencia or size hollow menos size process
	while(auxiliary!=NULL){//rrecorro list completa
		if(auxiliary->type=='p' || auxiliary->size<sizeProcess){//this block not was hollow or size of hollow is lest than size process
			auxiliary=auxiliary->next;
			continue;
		}else{
			if(auxiliary->size-sizeProcess<difference){//check if this hollow is best that other hollow readed anteriormente
				difference=auxiliary->size-sizeProcess;//update diferencia (difredencia is a flag)
				bestHollow=auxiliary;//set pointer best hollow 
			}
		}	
		auxiliary=auxiliary->next;
	}
	return bestHollow;
}
unsigned short getMaximunValueOfNextAddress(Node *head){
	unsigned short maximun=0;
	while(head!=NULL){
		if(head->nextAddress>maximun){
			maximun=head->nextAddress;
		}
		head=head->next;
	}
	return maximun;
}
Node *addProcess(Node **head,Node **hollow,Node *process){//this function recive that as parameter a hollow and process to insert in hollow the size hollow shuld mayor or same that size process
	if(*hollow==NULL || process==NULL){
		return NULL;
	}
	if((*hollow)->size<process->size){//second if
		return NULL;
	}
	process->address=(*hollow)->address;
	process->nextAddress=(*hollow)->nextAddress;
	if((*hollow)->previus==NULL){
		addNodeBeforeOf(head,process);
	}else{
		addNodeBeforeOf(hollow,process);
	}
	if((*hollow)->size>process->size){
		(*hollow)->address=process->address+process->size;
		(*hollow)->size-=process->size;
		(*hollow)->nextAddress=getMaximunValueOfNextAddress(*head)+8;
	}else{//just can ser same because second if was charged of validate case menor in conclusion size are same then not abra hollow
		removeNode(hollow);
	}
	return process;
}
void *trySetProcessInRAM(void *args){
	Node **head=(Node **)args;
	Node *process=getNode('p',0,((random()%7)+1)*1024,0,NULL,NULL);//get process, the proces size have a range of 1024 => 7168 always in multiples of 1024
	Node *bestHollow=bestFit(head,process->size);//get best hollow with algorith best fit
	if(bestHollow==NULL){//if bestHollow was NULL then NO find a hollow
		printf("bestHollow was NULL can't insert process in ram %d\n",process->size);	
		pthread_mutex_unlock(&mutex);
	}else{//find hollow
		unsigned short time=(random()%7)+1;
		addProcess(head,&bestHollow,process);
		//printf("process %d created with time %d\n",process->size,time);
		pthread_mutex_unlock(&mutex);
		sleep(time);
		process->type='h';
	}
	pthread_exit(NULL);//finish thread can use return NULL 
}
void *startGraphics(void *args){
	Display *display=getConnectionX11();
	int screen=getScreen(display);
	unsigned int widthDisplay=getWidthDisplay(display,screen);
	unsigned int heightDisplay=getHeightDisplay(display,screen);
	unsigned int widthPixelsByK=(widthDisplay/64);
	//printf("widthDisplay=%d\theightDisplay=%d\nwidthPixelsByK=%d\n",widthDisplay,heightDisplay,widthPixelsByK);
	Window father=getWindow(&display,screen,10,10,widthDisplay,heightDisplay);
	Window mapMemory=addChildWindow(&display,father,screen,0,0,widthDisplay,heightDisplay/3);
	addChildWindow(&display,father,screen,0,heightDisplay/3,widthDisplay,(heightDisplay/3)*2);
   XEvent event;
   unsigned int x=0;
	Node *auxiliary;
   while(1){
		auxiliary=head;
   	while(auxiliary!=NULL){
		//	printf("|%c|%x|%d|%x|->",auxiliary->type,auxiliary->address,auxiliary->size,auxiliary->nextAddress);
			if(auxiliary->type=='h'){
				XSetForeground (display, XDefaultGC (display,screen), BlackPixel(display, 0)^getColor(display, "green"));
			}else{
				XSetForeground (display, XDefaultGC (display,screen), BlackPixel(display, 0)^getColor(display, "red"));
			}
			XFillRectangle(display,mapMemory,XDefaultGC(display,screen),x,0,widthPixelsByK*(auxiliary->size/1024),(heightDisplay/3)*2);
			XFlush(display);
			x+=widthPixelsByK*(auxiliary->size/1024);
			auxiliary=auxiliary->next;
			if(auxiliary==NULL){
				x=0;
				auxiliary=head;
			}
      }
	//	printf("finish one cicle\n");
		XClearWindow(display,mapMemory);	
      XNextEvent(display,&event);
		usleep(137);
   }
	return NULL;	
}
void startSimulation(){
	srand(time(NULL));//start semilla for random
	pthread_mutex_init(&mutex,NULL);//start semaphore for threads

	pthread_t graphics;
	pthread_create(&graphics,NULL,startGraphics,NULL);

//	Node *head=NULL;
	addNode(&head,getNode('h',0,65535,8,NULL,NULL));//start "ram memory" as a hollow of 64K (2bytes=16 bits=>rango 0-65535) then (1024 => 1K) => (64K=>65536)
	while(1){//while(existHollow(head)){//while infinity
		pthread_mutex_lock(&mutex);
//		printRAM(head);
		pthread_t process;//thread
		pthread_create(&process,NULL,trySetProcessInRAM,(void *)&head);//start thread
		sleep(1);
	}
	pthread_join(graphics,NULL);
}
int main(){
	startSimulation();
	return 0;
}
