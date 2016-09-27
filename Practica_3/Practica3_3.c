//Practica 3_3
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int child = 0;
	int i = 0;
	int contsize = 0;
	int z = 0;
	int array_index = 0;
	int readSuccess = 0;
	char burst_read[5];
	char nameFiles[14];
	char nameFile1[7];
	char nameFile2[7];
	char *cpPath = "/bin/cp";
	char *args[3];

	for (i = 0; i < sizeof(nameFiles); i++)
	{
		nameFiles[i] = '1';
	}

	for (i = 0; i < sizeof(nameFile1); i++)
	{
		nameFile1[i] = ' ';
	}

	for (i = 0; i < sizeof(nameFile2); i++)
	{
		nameFile2[i] = ' ';
	}
	printf("Input origin file name and destiny file name \n");
	do{
		readSuccess = read(0, burst_read, sizeof(burst_read));
		if (readSuccess != 0){
			for (i = 0; i < 5; i++)
			{
				nameFiles[array_index] = burst_read[i];
				array_index = ++array_index;
			};
		}
	}while(readSuccess != 0);
	i = 0;
	for (contsize = 0; contsize <= sizeof(nameFiles); contsize++){
		if (nameFiles[i] != ' '){
			if (i < 7){
				nameFile1[i] = nameFiles[i];
				i = ++i;
			}else{
				nameFile2[z] = nameFiles[i];
				z = ++z;
				i = ++i;
			}
		}else{
			i = ++i;

		}
	}
	args[0] = cpPath;
	args[1] = nameFile1;
	args[2] = nameFile2;
	args[3] = NULL;
	child = fork();
	if (child == 0){
		execv (cpPath, args);
	}else{
		wait(NULL);
		printf("DONE\n");
	}
	
	return 0;
}