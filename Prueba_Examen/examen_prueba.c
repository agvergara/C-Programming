#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int fd1[2];
    int fd2[2];
    int retpipe = 0;
    int retopen = 0;
    int retcreat = 0;
    int retread = -999;
    int retwrite = -999;
    char buffer[500];
    char caracter;
    int contador = 0;
    int i = 0;
    int child = -999;
    char confirm[500];
    int dupreturn = 0;
    int bytesRecibidos = 0;
    int aux = 0;
    int retdup = 0;

    retcreat = open(argv[2], O_CREAT|O_RDWR|O_APPEND);
    retpipe = pipe(fd1);
    retpipe = 0;
    retpipe = pipe(fd2);
    child = fork();

    if (child == 0){
        close(fd2[0]);
        close(fd1[1]);
        retdup = dup2(fd1[0], 0);
        retdup = dup2(fd2[1], 1);
        char *args[] = {"./ponmayusculas", NULL};
        execve("./ponmayusculas", args, NULL);
    }else{
        retopen = open(argv[1], O_RDONLY);
        close(fd1[0]);
        close(fd2[1]);
        do{
            //LEER LETRA A LETRA AQUI
            retread = read(retopen, &caracter, 1);
            if (caracter != '\n'){
                buffer[i] = caracter;
                i++;
            }else{
                buffer[i+1] = '\0';
                printf("%c\n", buffer[4]);
                contador++;
                i = i + 1;
                if ((contador % 2) != 0){
                    retwrite = write(fd1[1], &i, sizeof(i));
                    retwrite = -999;
                    retwrite = write(fd1[1], &buffer, i);
                    retread = read(fd2[0], &confirm, sizeof(confirm));
                }else{
                    retwrite = write(retcreat, &buffer, i);
                }
                for (i = 0; i < sizeof(buffer); i++) {
                    buffer[i] = ' ';
                }
                i = 0;

            }
            /*for (i = 0; i < sizeof(buffer); i++) {
                if (buffer[i] == '\n'){
                    contador++;
                    aux = (i - aux) + 1;
                    if ((contador % 2) != 0){
                        retwrite = write(fd1[1], &aux, sizeof(aux));
                        retwrite = -999;
                        retwrite = write(fd1[1], &buffer, aux);
                        retread = read(fd2[0], &confirm, sizeof(confirm));
                    }else{
                        retwrite = write(retcreat, &buffer, aux);
                    }
                    aux = i;
                }
            }*/
        }while(retread != 0);
    }
    return 0;
}
