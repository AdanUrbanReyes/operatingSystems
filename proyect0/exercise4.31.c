#include <stdio.h>
#define diameter 9//this number always shuld integer impar
int main(){
	int spacesToPrint,characteresToPrint;
	int cp,sp,flatCharacteres=2,flatSpaces=-1;//cp characteres printed, sp spaces printed
	for(characteresToPrint=1,spacesToPrint=diameter/2;			characteresToPrint>0			;spacesToPrint+=flatSpaces,characteresToPrint+=flatCharacteres){
		for(sp=1;sp<=spacesToPrint;sp++)
			printf(" ");
		for(cp=1;cp<=characteresToPrint;cp++)
			printf("*");
		if(characteresToPrint==diameter){
			flatCharacteres=-2;
			flatSpaces=1;
		}
		printf("\n");
	}
	return 0;
}
