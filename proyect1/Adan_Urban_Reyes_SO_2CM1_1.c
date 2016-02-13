#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#define gigabyte 1073741824

//#include <sys/time.h>

/*
	this program was testing on toshiba satellite psst-b
	whit nexting caracteristicas:
	16 gigabytes in RAM
	processor intel core i7
	8 nucleos virtuales
	4 nucleos fisicos
	hard disc 1TB (5400 RPM)


   1segundo=10^6microsegundos
   1segundo=10^9nanosegundos
   10^6microsegundos=10^9nanosegundos
   1microsegundo=10^3nanosegundos
   usleep(microsegundos);
   1024bytes=1kilobyte
   1024^2=1048576bytes=1megabyte
   1024^3=1073741824bytes=1gigabyte
*/
long nanoseconds4096RAM,nanoseconds4096HARDDISC;
long averageNanoSeconds;
void printWithFormatString(char *string,int tope){
	int i=tope-strlen(string);
	printf("%s",string);
	while((i--)>0)
		printf(" ");
}
void printWithFormatInteger(long integer,int tope){
	char *string=(char *)malloc(sizeof(char)*20);
	sprintf(string,"%ld",integer);
	printWithFormatString(string,21);
}
int openFile(char *path,int flags,mode_t mode){
	int descriptor=open(path,flags,mode);
	if(descriptor<0){
		printf("error open file %s\n",path);
		exit(-3);
	}
	return descriptor;
}
/*void initTimer(struct timval *timer){
	if(gettimeofday(timer,NULL)==-1){
		printf("error inicializando timer\n");
		exit(-3);
	}
}*/
void inicializaTimer(struct timespec *timer){
	if(clock_gettime(CLOCK_REALTIME,timer)==-1){
		printf("error inicializando timer\n");
		exit(-3);
	}
}
/*struct timespec getTime(struct timeval start,struct timeval end){
	struct timeval time;
	time.tv_sec=end.tv_sec-start.tv_sec;
	time.tv_nsec=end.tv_usec-start.tv_usec;
	return time;
}*/
struct timespec getTime(struct timespec start,struct timespec end){
	struct timespec time;
	long nanoseconds=(end.tv_sec*1000000000+end.tv_nsec)-(start.tv_sec*1000000000+start.tv_nsec);
	time.tv_sec=nanoseconds/1000000000;
	time.tv_nsec=nanoseconds%1000000000;
	return time;
}
void resizeBuffer(char **buffer,unsigned int size){
	struct timespec start,end,time;
	if(*buffer!=NULL){
		free(*buffer);
	}
	inicializaTimer(&start);
	*buffer=(char *)malloc(sizeof(char)*size);
	if(*buffer==NULL){
		printf("error resizing buffer\n");
		exit(-7);	
	}
	memset(*buffer,'7',size);
	inicializaTimer(&end);
	time=getTime(start,end);	
	if(size==4096){
		nanoseconds4096RAM=time.tv_sec*1000000000+time.tv_nsec;
	}
	//printf("size=%d",size);
	//printf("seconds=%ld\n",time.tv_sec);
	//printf("nanoseconds=%ld\n\n",time.tv_nsec);
}
char writeFile(char *path,char *buffer,int bytes){
	struct timespec start,end,time;
	long nanoSecondsBySecond;
	int fileDescriptor=openFile(path,O_CREAT|O_WRONLY|O_TRUNC,0666);
	inicializaTimer(&start);
	write(fileDescriptor,buffer,bytes);
	close(fileDescriptor);
	inicializaTimer(&end);
	time=getTime(start,end);
	nanoSecondsBySecond=time.tv_nsec/bytes;
	printWithFormatInteger(bytes,21);
	printWithFormatInteger(time.tv_sec,21);
	printWithFormatInteger(time.tv_nsec,21);
	printWithFormatInteger(nanoSecondsBySecond,21);
	printf("\n");
	averageNanoSeconds+=nanoSecondsBySecond;
	if(bytes==4096){
		nanoseconds4096HARDDISC=time.tv_sec*1000000000+time.tv_nsec;
	}
	return 0;
}
void startMediciones(){
	char *buffer=NULL,*nameFile=(char *)malloc(sizeof(char)*17);
	unsigned int bytes,iteraciones,potTen;
	for(bytes=1,iteraciones=0,potTen=10;bytes<=gigabyte;iteraciones++){
		if(bytes>potTen){
			sprintf(nameFile,"write%d.txt",potTen);
			resizeBuffer(&buffer,potTen);
			writeFile(nameFile,buffer,potTen);
			potTen*=10;
		}else{
			sprintf(nameFile,"write%d.txt",bytes);
			resizeBuffer(&buffer,bytes);
			writeFile(nameFile,buffer,bytes);
			bytes*=2;
		}
	}
	free(buffer);
	printf("El promedio se tarda %ld nanosegundos en escribir un byte en RAM\n",(long)(averageNanoSeconds/iteraciones));
}
int main(){
	struct timespec start,end,time;
	inicializaTimer(&start);
	printf("Medicion de tiempos de acceso a RAM\nAlumno: Adan Urban\n\n");
	printWithFormatString("Tamano del arreglo",21);
	printWithFormatString("Tiempo total",42);
	printWithFormatString("Tiempo por byte",21);
	printf("\n");
	printWithFormatString("Bytes",21);
	printWithFormatString("s",21);
	printWithFormatString("ns",21);
	printWithFormatString("nanosegundos",21);
	printf("\n");
	startMediciones();
	inicializaTimer(&end);
	time=getTime(start,end);
	printf("El tiempo total de ejecucion de este programa = %ld segundos %ld nanosegundos\n",time.tv_sec,time.tv_nsec);
	long relation=nanoseconds4096HARDDISC/nanoseconds4096RAM;
	printf("En esta computadora escribir 4096 bytes a disco duro tarda %ld veses mas que escribir 4096 bytes en RAM\n",relation);
	return 0;
}
