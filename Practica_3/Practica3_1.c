#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

//write 0 -> standard input
//write 1 -> standard output
//write 2 -> standard error
//Same for read

int main (int argc, char *argv[]){
	int success_open = 0;
	char file_chars[50];
	char burst_read[5];
	int read_return = 0;
	int write_return = 0;
	int array_index = 0;
	int bytesRead = 0;
	int i = 0;
	
	//inicializacion de arrays a 0

	for (i = 0; i < sizeof(file_chars); i++)
	{
		file_chars[i] = 0;
	}

	for (i = 0; i < sizeof(burst_read); i++)
	{
		burst_read[i] = 0;
	}	
	do{
		read_return = read(0, burst_read, 5);
		if (read_return != 0){
			for (i = 0; i < 5; i++)
			{
				file_chars[array_index] = burst_read[i];
				array_index = ++array_index;
			};
		}
		bytesRead = bytesRead + read_return;
	}while (read_return != 0);
	if (argc > 1){
		success_open = open (argv[1], O_CREAT|O_WRONLY, 0777);
		write_return = write (success_open, file_chars, bytesRead);
		printf("DONE\n");
		close(success_open);
	}else{
		write_return = write (1, file_chars, bytesRead);
	}
	return 0;
}