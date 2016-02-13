#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int main(){
	srand(time(NULL)); 
	char workOrSleep;
	long int miliSeconds=0;
	long int secondsTotal=0,workMiliSeconds=0,sleepMiliSeconds=0;
	
	while(secondsTotal<=10000){
		workOrSleep=(char)(rand()%1);
		miliSeconds=(rand()%99)+1;
		if(workMiliSeconds>=5000){
			workOrSleep=0;
		}
		if(sleepMiliSeconds>=5000){
			workOrSleep=1;
		}
		if(workOrSleep==1&&workMiliSeconds<=5000){//work
			usleep(miliSeconds*1000);
			workMiliSeconds+=miliSeconds;
		}else{//sleep
			if(sleepMiliSeconds<=5000){
				usleep(miliSeconds*1000);
				sleepMiliSeconds+=miliSeconds;
			}
		}
		secondsTotal+=miliSeconds;
	}
	printf("secondsTotal=%ld\n",secondsTotal);
	return 0;
}
