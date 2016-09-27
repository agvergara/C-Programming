#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main (int argc, char *argv[]){
	int child = 0;
	int cont = 0;
	int pipe[2];
	int read_return = 0;
	int success_write = 0;
	int sum[2];

	pipe(pipe);
	child = fork();
	if (child == -1){
		printf("That was awkward, could not create child\n");
		exit(1);
	}
	if (child == 0){
		//Child time!
		//Reading from pipe! WOW!


	}else{
		// Parent time!
		read_return = read (0, sum[0], 1);
		if (read_return == 1){
			read_return = read (0 ,sum[1], 1);
		}else{
			printf("Could not read first integer\n");
			exit(1);
		}

		//Pipe writing time!
		success_write = write (pipe[1], sum[0], 1);
		if (success_write == 1){
			success_write = write(pipe[1], sum[1], 1);
		}else{
			printf("Could not write first integer\n");
			exit(1);
		}

		//Pipe result reading time!

	}
}
