#include <unistd.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
	int contador = 1;
	int pipe[2];
	int bufferP[10];

	do{
		printf("%d\n", contador);
		write(pipe[1], bufferP, 10);
		contador = ++contador;
	}while (1);


	return 0;
}