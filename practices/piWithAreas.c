#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <float.h>
#define radio 1
long double getY(long double x){
	if(pow(x,2)>1){
//		printf("x=%Lf\n",x);
		return 0;
	}
	return sqrt(1-pow(x,2));
}
long double getArea(long double x1,long double y1,long double x2,long double y2){
	return (((y1+y2)*(x2-x1))/2);//A=(BaseMayor+baseMenor)/2
}
long double getPlusAreas(long double xStart,long double xEnd,long double sizeDivicions){
	long double x1,y1,x2,y2,plus=0;
	printf("xStart=%Lf xEnd=%Lf sizeDivicions=%Lf",xStart,xEnd,sizeDivicions);
	x1=xStart;
	y1=getY(x1);
	x2=x1+sizeDivicions;
	y2=getY(x2);
	while(x2<=xEnd){
		plus+=getArea(x1,y1,x2,y2);
		x1=x2;
		y1=y2;
		x2=x1+sizeDivicions;
		y2=getY(x2);	
	}
	return (plus*4);
}
unsigned int getDivisionsByProcess(long double divisions,unsigned char *process){
	if(divisions<*process){
		*process=(unsigned char)divisions;
		return 1;
	}
	return (divisions/(*process));
}
int main(int ari,char **arc){//./nameExecutable numberDivisions numberProcess
	if(ari<3){
		printf("execute like %s numberDivisions numberProcess\n",arc[0]);
		return 0;
	}
	//int tuberia[2];
	//pipe(tuberia);//[1] writer [0] reader
	pid_t pid;
	long double divisions,sizeDivisions,plus,xStart=0,xEnd;
	unsigned int divisionsByProcess;
	unsigned char process,i;
	divisions=strtold(arc[1],NULL);//set number of divisions enter by terminal, entre more divisions plus se hacerca more to pi/4
	process=atoi(arc[2]);
	sizeDivisions=(radio/divisions);//set sizeDivicions
	divisionsByProcess=getDivisionsByProcess(divisions,&process);
	printf("divisionsByProcess=%d\n",divisionsByProcess);

	for(i=0,xEnd=sizeDivisions*divisionsByProcess;i<process;i++){
		pid=fork();
		if(pid==0){//is son
			/*printf("sizeDivisions=%Lf\n",sizeDivisions);
			printf("divisions=%Lf\n",divisions);
			printf("xStart%Lf\txEnd=%Lf\n\n",xStart,xEnd);*/
			sleep(i);
			plus=getPlusAreas(xStart,xEnd,sizeDivisions);	
			//write(tuberia[1],&plus,sizeof(long double));
			printf("plus=%.*Lf\n\n",15,plus);
			return 0;
		}else{
			if(pid<0){//is a error
				printf("error creating process %d\n",i);
			}
		}
		xStart=xEnd;
		if(i==(process-2)){
			xEnd=radio;
		}else{
			xEnd*=divisionsByProcess;
		}
	}
	wait(NULL);
	/*long double finalPlus,aux;
	for(i=0;i<process;i++){
		read(tuberia[0],&aux,sizeof(long double));
		finalPlus+=aux;
	}
	printf("finalPlus=%.*Lf\n\n",17,finalPlus);
	*/
/*	printf("process=%d\n",process);
	printf("sizeDivisions=%Lf\n",sizeDivisions);
	printf("divisions=%Lf\n",divisions);
	printf("plus=%Lf\n",plus);*/
	return 0;	
}
