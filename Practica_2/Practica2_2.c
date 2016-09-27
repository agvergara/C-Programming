#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

//write 0 -> standard input
//write 1 -> standard output
//write 2 -> standard error
//Same for read

int main (int argc, char const *argv[]){
	int success_open = open(argv[1], O_RDONLY);
	int buffer = 4000;
	char file_chars[4000];
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

	if (success_open == -1){
		printf("This is awkward, could not open file (it exists?)\n");
		return -1;
	}else{
		do{
			read_return = read(success_open, burst_read, buffer);
			if (read_return != 0){
				for (i = 0; i < buffer; i++)
				{
					file_chars[array_index] = burst_read[i];
					array_index = ++array_index;
				};
			}
			bytesRead = bytesRead + read_return;
		}while (read_return != 0);
		close (success_open);
		success_open = open (argv[2], O_CREAT|O_WRONLY, 0777);
		write_return = write (success_open, file_chars, bytesRead);
		close(success_open);
		printf("DONE\n");
	}
	return 0;
}