#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
int main(int ari,char **arc){
	struct timeval start,end;
	time_t seconds;//miliSeconds,nanoSeconds;
	time_t tope=atoi(arc[1]);
	gettimeofday(&start,NULL);
	int fd;
	char caracter='X';
	fd=open("archivo.txt",O_WRONLY|O_CREAT,0666);
	while(seconds<tope){
		write(fd,&caracter,1);
		gettimeofday(&end, NULL);
		seconds  = end.tv_sec  - start.tv_sec;
		//nanoseconds = end.tv_usec - start.tv_usec;
		//miliSeconds = ((seconds) * 1000000 + nanoSeconds/1000.0) + 0.5;
	}
	sync();
	close(fd);
	return 0;
}
