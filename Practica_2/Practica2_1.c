#include <stdio.h>
#include <unistd.h>

//write 0 -> standard input
//write 1 -> standard output
//write 2 -> standard error

int main (int args, char *argc[]){
	char *message = "Hola mundo!\n";

	if (write(1, message, 13) != 13){
		write(2, "This is awkward\n", 17);
		return -1;
	}

	return 0;
}