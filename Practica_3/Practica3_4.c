#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main (int argc, char *argv[]){
	int success_open = 0;
	char file_chars[50];
	char burst_read[5];
	int read_return = 0;
	int write_return = 0;
	int write_return_print = 0;
	int array_index = 0;
	int bytesRead = 0;
	int fifoFile = 0;
	int i = 0;
	
	//initialize arrays
	success_open = open (argv[1], O_CREAT|O_WRONLY, 0777);
	for (i = 0; i < sizeof(file_chars); i++)
	{
		file_chars[i] = ' ';
	}

	for (i = 0; i < sizeof(burst_read); i++)
	{
		burst_read[i] = ' ';
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
		write_return_print = write (1, file_chars, bytesRead);
		write_return = write (success_open, file_chars, bytesRead);
		for (i = 0; i < sizeof(file_chars); i++)
		{
			file_chars[i] = ' ';
		}
		array_index = 0;
		bytesRead = 0;
	}while (read_return != 0);
	printf("DONE\n");
	close(success_open);
	return 0;
}