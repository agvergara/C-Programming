#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

//El argc es: contador de argumentos (3 argumentos por ejemplo)
//El argv es: un vector de argumentos (ver mas abajo)

int main (int args, char *argc[]){
	char *currentPath = "./";
	char *lsPath = "/bin/ls";
	char *argv[] = {lsPath, currentPath, NULL};
	int childNum = 1;
	int childArray[childNum];

	childArray[0] = fork();
	if (childArray[0] == 0){
		execv (lsPath, argv);
	}else{
		wait(NULL);
	}
	return 0;
}