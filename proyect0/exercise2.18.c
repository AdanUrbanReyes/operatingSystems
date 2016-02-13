#include <stdio.h>
#include <stdlib.h>
#define numbersToReceive 2
int *getGreaterLowerNumber(int *numbers,int size){
   if(size==0)
      return NULL;
   int i,*greaterLowerNumber;
   greaterLowerNumber=(int *)malloc(sizeof(int)*2);//this array contains number greater(index 0) and number lower index(1)
   *(greaterLowerNumber+0)=*(greaterLowerNumber+1)=*(numbers+0);
   for(i=0;i<size;i++){
      if(*(greaterLowerNumber+0)<*(numbers+i)){
         *(greaterLowerNumber+0)=*(numbers+i);//put as greater number
      }
      if(*(greaterLowerNumber+1)>*(numbers+i)){
         *(greaterLowerNumber+1)=*(numbers+i);//put as lower number
      }
   }
   return greaterLowerNumber;
}
int main(){
   int i,*greaterLowerNumber,*numbers=(int *)malloc(sizeof(int)*numbersToReceive);
   printf("enter %d numbers\n",numbersToReceive);
   for(i=0;i<numbersToReceive;i++){
      scanf("%d",(numbers+i));
   }
   greaterLowerNumber=getGreaterLowerNumber(numbers,numbersToReceive);
   if(*(greaterLowerNumber+0)==*(greaterLowerNumber+1)){
      printf("these numbers are equals\n");
		return 0;
	}
   printf("%d is larger\n",*(greaterLowerNumber+0));
   return 0;
}
