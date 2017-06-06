#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int fdchild[2]; /* pipe child */
  int fdparent[2]; /* parent pipe */
  int retopen1 = -99999; /*return open data file*/
  int retopen2 = -99999; /*return open output file*/
  int child = -99999; /* return fork */
  int retpipe = -99999; /*return pipe */
  int retread = -99999; /* return read */
  int retreadpipech = -9999; /*return read pipe child */
  int retwritepipech = -9999; /*return write pipe child */
  int retreadpipepar = -9999; /*return read pipe parent */
  int retwritepipepar = -9999; /*return write pipe parent */
  int retwriteres = -9999; /*Write the result */
  int retdup = -9999; /* return dup2 */
  int i = 0;
  int j = 0;
  int cont = 0;
  int lines = 0;
  int auxlines = 0;
  int operations = 0;
  int status = -999;
  char mander;
  char buffer[1024];
  char result[32];
  char quit[5] = "quit\n";

  int flag = 1;


  for (j = 0; j < sizeof(buffer); j++) {
    buffer[j] = ' ';
  }

  for (j = 0; j < sizeof(result); j++) {
    result[j] = ' ';
  }

  retpipe = pipe(fdchild);
  retpipe = -99999;
  retpipe = pipe(fdparent);
  child = fork();

  if (child == 0){
    close(fdchild[1]); /* Read from parent*/
    close(fdparent[0]); /* Write to parent*/
    close(1);
    close(0);

    retdup = dup2(fdchild[0], 0);
    retdup = dup2(fdparent[1], 1);

    close(fdchild[0]);
    close(fdparent[1]);

    char *args[] = {"/usr/bin/bc", NULL};
    execvp("/usr/bin/bc", args);
    /*char *args[] = {"/bin/cat", NULL};
    execvp("/bin/cat", args);*/
    perror("execve failed");
  }else{
    close(fdchild[0]); /* Write to child */
    close(fdparent[1]); /* Read from child */
    retopen1 = open(argv[1], O_RDONLY);
    retopen2 = open(argv[2], O_CREAT|O_RDWR|O_TRUNC, 0777); /*Open (or create) the solution file */
    do{
      retread = read(retopen1, &mander, 1);
      if (mander == '\n'){
        lines++;
      }
    }while(retread != 0);

    retread = -9999;
    mander = ' ';
    close(retopen1);
    retopen1 = -9999;
    retopen1 = open(argv[1], O_RDONLY);

    do{
      retread = read(retopen1, &mander, 1);
      if (mander != '\n'){
        if (mander == '/'){
          flag = flag * -1;
        }
        if (flag == 1){
          if (mander != '/'){
            buffer[i] = mander;
            i++;
            flag = 1;
          }
        }
      }else{
        auxlines++;
        buffer[i] = '\n';
        for (j = 0; j < i; j++) {
          if (buffer[j] == 'A'){
            if (buffer[j+1] == 'D'){
              buffer[j] = ' ';
              buffer[j+1] = '+';
              buffer[j+2] = ' ';
              operations++;
            }
          }else if(buffer[j] == 'S'){
            if (buffer[j+1] == 'U'){
              buffer[j] = ' ';
              buffer[j+1] = '-';
              buffer[j+2] = ' ';
              operations++;
            }
          }else if(buffer[j] == 'M'){
            if (buffer[j+1] == 'U'){
              buffer[j] = ' ';
              buffer[j+1] = '*';
              buffer[j+2] = ' ';
              operations++;
            }
          }else if(buffer[j] == 'D'){
            if (buffer[j+1] == 'I'){
              buffer[j] = ' ';
              buffer[j+1] = '/';
              buffer[j+2] = ' ';
              operations++;
            }
          }
        }
        if (retwritepipepar == -99999){
          cont++;
        }
        if (auxlines == lines){
          retwritepipepar = write(fdchild[1], quit, sizeof(quit));
        }else{
          if (buffer[0] != '\n'){
            if (cont < lines){
              retwritepipepar = write(fdchild[1], buffer, i + 1); /* Give the child the data */
              retreadpipepar = read(fdparent[0], &result, sizeof(result));
              buffer[i] = ' ';
              buffer[i+1] = '=';
              buffer[i+2] = ' ';
              i = i + 3;
              for (j = 0; j < sizeof(result); j++) {
                if (result[j] != '\n'){
                  buffer[i] = result[j];
                  i++;
                }
              }
              buffer[i+1] = '\n';
              buffer[i+2] = '\0';
              retwriteres = write(retopen2, buffer, i+2);
              for (j = 0; j < sizeof(buffer); j++) {
                buffer[j] = ' ';
              }
              for (j = 0; j < sizeof(result); j++) {
                result[j] = ' ';
              }
            }
          }
          i = 0;
          retwritepipepar = -99999;
          retreadpipepar = -9999;
        }
      }
    }while(retread != 0);
    wait(&status);
    printf("Hay %i lineas en el fichero\n", lines-1);
    printf("De las cuales %i son operaciones artimeticas\n", operations);
    printf("El valor de retorno del hijo es: %i\n", WEXITSTATUS(status));
  }

  return 0;
}
