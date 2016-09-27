#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (int args, char *argc[]){
	int i = 0;
	int childNum = 2;
	int childPID = 0;
	int printchildPID[childNum];

	for (i = 0; i < childNum; i++){
		childPID = fork();
		if (childPID == 0){
			printf ("I am child %d and here's my PID: %d \n", i, getpid());
			break;
		}else if (childPID == -1){
			printf("FORK NOT SUCCEED\n");
			break;
		}else if (childPID > 0){
			printchildPID[i] = childPID;
		}
	}
	
	if (childPID > 0){
		printf("I am the father and heres my sons PIDs: ");
		for (i = 0; i < childNum; i++){
			printf("%d ", printchildPID[i]);
		}
		printf("\n");
	}

	return 0;
}