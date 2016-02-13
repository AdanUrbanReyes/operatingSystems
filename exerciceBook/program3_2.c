#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/*
	functions on terminal
	pstree
	ps -A | grep id
*/
int main(void){
	pid_t idProcess;
	pid_t idFather;
	uid_t idUserReal=getuid();
	uid_t idUserEfectivo=geteuid();
	idProcess=getpid();
	idFather=getppid();
	printf("idUserReal=%d\n",idUserReal);
	printf("idUserEfectivo=%d\n",idUserEfectivo);
	printf("idProcess=%d\n",idProcess);
	printf("idFather=%d\n",idFather);
	sleep(40);
	return 0;
}
