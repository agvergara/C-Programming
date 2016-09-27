#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main (int args, char *argc[]){
	int status = 0;
	int resch0 = 0;
	int resch1 = 0;
	int i = 0;
	int sum1 = 2;
	int sum2 = 5;
	int childNum = 2;
	int childs[childNum];

	for (i = 0; i < childNum; i++){
		childs[i] = fork();
	}

	if (childs[0] == 0){
		resch0 = sum1 + sum2;
		exit(resch0);
	}else if (childs[1] == 0){
		resch1 = sum1 * sum2;
		exit(resch1);
	}else{
		wait(&resch0);
		wait(&resch1);
		printf("Los resultados de mis hijos son: %d y %d \n", WEXITSTATUS(resch0), WEXITSTATUS(resch1));
	}
}