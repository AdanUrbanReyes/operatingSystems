#include <stdio.h>
#include <stdlib.h>
#define numbersToReceive 3
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
unsigned char areNumbersDistinct(int *numbers,int size){//return 0 (true) if array contains numbers equals else return 1
   int i,j;
   for(i=0;i<size;i++){
      for(j=i+1;j<size;j++){
         if(*(numbers+i)==*(numbers+j))
            return 0;
      }
   }
   return 1;
}
int plusIntegers(int *numbers,int size){
   if(size==0)
      return 0;
   int i,plus=0;
   for(i=0;i<size;i++){
      plus+=*(numbers+i);
   }
   return plus;
}
float averageIntegers(int *numbers,int size){
   if(size==0)
      return 0;
   int plus=plusIntegers(numbers,size);
   return (plus/size);
}
int productIntegers(int *numbers,int size){
   if(size==0)
      return 0;
   int i,product=1;
   for(i=0;i<size;i++){
      product*=*(numbers+i);
   }
   return product;
}
void printIntegerArray(int *numbers,int size,char separator){
   int i;
   for(i=0;i<size;i++){
      printf("%d%c",*(numbers+i),separator);
   }
}
int main(){
   int i,*greaterLowerNumber,*numbers=(int *)malloc(sizeof(int)*numbersToReceive);
   printf("enter %d numbers\n",numbersToReceive);
   for(i=0;i<numbersToReceive;i++){
      scanf("%d",(numbers+i));
   }
   if(!areNumbersDistinct(numbers,numbersToReceive)){
      printf("please enter numbers distinct\n");
      return -1;
   }
   printf("Input three different integers: ");
   printIntegerArray(numbers,numbersToReceive,' ');
   printf("\nSum is %d\n",plusIntegers(numbers,numbersToReceive));
   printf("Average is %f\n",averageIntegers(numbers,numbersToReceive));
   printf("Product is %d\n",productIntegers(numbers,numbersToReceive));
   greaterLowerNumber=getGreaterLowerNumber(numbers,numbersToReceive);
   printf("Smallest is %d\n",*(greaterLowerNumber+1));
   printf("Largerst is %d\n",*(greaterLowerNumber+0));
   return 0;
}
