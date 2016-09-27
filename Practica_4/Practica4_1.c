#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (int argc, char *argv[]){

	int fd[2];

	int i = 0;
	int z = 0;
	int k = 0;
	int j = 0;
	int child = 0;
	int child2 = 0;
	int pipe_return = 0;
	int read_return_child = 1;
	int open_file_child = 0;
	int open_data_file = 0;
	int open_return_file = 0;
	int status = 0;
	char file_line[26];
	char alias[10];
	char file1[10];
	char file2[10];
	char byte = ' ';

	int write_pipe = 0;

	char lineStatus = 0;

	char *data_file[3];


	//Inicializacion array
	for (i = 0; i < sizeof(file_line); i++){
		file_line[i] = ' ';
	}	

	for (i = 0; i < sizeof(alias); i++){
		if (i == 0){
			alias[i] = '.';
			file1[i] = '.';
			file2[i] = '.';
		}else if (i == 1){
			alias[i] = '/';
			file1[i] = '/';
			file2[i] = '/';
		}else{
			alias[i] = ' ';
			file1[i] = ' ';
			file2[i] = ' ';
		}
	}	

	pipe_return = pipe(fd);

	if (pipe_return == -1){
		printf("Could not create pipe\n");
		return 0;
	}

	z = 2;
	k = 2;
	j = 2;
	i = 0;

	if (argc < 2 || argc > 2){
		printf("Wrong usage: ./Practica4_1 CmdFile\n");
	}else{
		pipe_return = pipe(fd);
		if (pipe_return == -1){
			printf("Could not create pipe\n");
			return 0;
		}
		child = fork();
		if (child == 0){
			close(fd[0]);
			//Child
			open_file_child = open(argv[1], O_RDONLY);
			if (open_file_child != -1){
				// Es 0 cuando termina el fichero
				do{
					read_return_child = read(open_file_child, &byte, 1);
					if (read_return_child == 0){
						break;
					}
					if (byte != '\n'){
						file_line[i] = byte;
						i = ++i;
					}else{
						for (i = 0; i < sizeof(file_line); i++)
						{
							if (i < 8){
								alias[z] = file_line[i];
								z = ++z;
							}else if (i > 8 && i < 17){
								file1[k] = file_line[i];
								k = ++k;
							}else if (i > 17){
								file2[j] = file_line[i];
								j = ++j;
							}
						}
						// Read new line
						z = 2;
						j = 2;
						k = 2;
						i = 0;

						alias[10] = '\0';
						file1[10] = '\0';
						file2[10] = '\0';
						open_data_file = open(file1, O_RDONLY);
						open_return_file = open(file2, O_CREAT | O_WRONLY, 0777);
						data_file[0] = alias;
						data_file[1] = file1;
						data_file[2] = NULL;
						child2 = fork();
						if (child2 == -1){
							exit(-1);
						}else if (child2 == 0){
							dup2(open_return_file, 1);
							dup2(open_return_file, 2);
							close(open_return_file);
							execve(data_file[0], data_file, NULL);	
						}
						wait(&status);
						if (WEXITSTATUS(status) == -1){
							write_pipe = write(fd[1], "2", 1);
						}else if (read_return_child != 0){
							write_pipe = write(fd[1], "1", 1);
							close(open_return_file);
						}
					}
				}while(read_return_child != 0);
				write_pipe = write(fd[1], "0", 1);
				close(fd[1]);
				exit(0);
			}else{
				//Bad execution
				exit(1);
			}
		}else if (child == -1){
			printf("Could not create child\n");
			return 0;
		}else{
			close(fd[1]);
			//Parent
			while(1){
				pipe_return = read(fd[0], &lineStatus, 1);
				if (lineStatus == '1'){
					printf("Ejecucion correcta\n");
				}else if (lineStatus == '2'){
					printf("Ejecucion incorrecta\n");
				}else{
					close(fd[0]);
					wait(&status);
					if (WEXITSTATUS(status) == 0){
						printf("FINALIZACION DE PROGRAMA CORRECTA\n");
					}else{
						printf("FINALIZACION DE PROGRAMA INCORRECTA\n");
					}
					break;
				}
			}
		}
	}
	return 0;
}