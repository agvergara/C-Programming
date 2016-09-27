//Practica 3.2
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int child;
	char *cpPath = "/bin/cp";
	char *args[] = {cpPath,argv[1], argv[2], NULL};

	if (argc < 2){
		printf("Wrong Usage (./Practica3_2 originFile destinyFile\n");
	}else{
		child = fork();
		if (child == 0){
			execv (cpPath, args);
		}else{
			wait(NULL);
		}
	}
	
	return 0;
}
