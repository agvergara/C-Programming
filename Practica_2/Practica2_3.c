#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int i = 0;
	printf("Number of arguments (argc) = %d\n", argc);
	printf("The first line argument (argv) si the executable name = %s\n", argv[0]);
	for (i = 1; i < argc; i++)
	{
		printf("The line argument %d is = %s\n", i, argv[i]);
	}
	return 0;
}