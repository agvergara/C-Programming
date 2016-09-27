#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int read_return = 0;
	int i = 0;
	int array_index = 0;
	char read_all[30];
	char read_burst[5];
	printf("Write a string(Press ctrl+D to stop reading): \n");
	do{
		read_return = read (0, read_burst, 5);
		if (read_return != 0){
			for (i = 0; i < 5; i++)
			{
				read_all[array_index] = read_burst[i];
				array_index = ++array_index;
			};
		}
	}while (read_return != 0);
	printf("You wrote: \n");
	for (i = 0; i < 3; i++)
	{
		write(1, read_all, sizeof(read_all));	
	}
	return 0;
}