#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]){    
    int A = 15;
    for(int i = 0 ; i < 1e7; i++)
        printf("%x", A);
    return 0;
}
    