#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<internal_commands.h>

/* 
  return 0 : no redirection
  return 1 : input redirection
  return 2 : output redirection
  corta de la listas los "<" y ">" y los nombres de los archivos de redireccion
  devuelve los archivos de redireccion en file_name
*/
int check_redirection(char* argv[],char file_name[]){
    int i = 0;
    while (argv[i] != NULL) {
    printf("%s\n", argv[i]);
        if (!strcmp(argv[i],"<")) {
            strcpy(file_name,argv[i+1]);
            //cut(argv, i);
      cut(argv, i);
      printf("red 1\n");
            return 1; //input
        }
    else if (!strcmp(argv[i],">")) {
            strcpy(file_name,argv[i+1]);
            cut(argv, i);
            cut(argv, i);
            printf("red 2\n");
            return 2; //output
        }
    i++;
    }
  printf("red 0\n");
    return 0;
}

void comprobar(char* argvs[]){ //acordar de vaciar buffer despues de cada comando
  char file_name[256];
  char buffer_secundario[1000];
  printf("a check red\n");
  int redir = check_redirection(argvs, file_name);
  switch (redir)
  {
  case 1:
    change_stdin(file_name);
    /*if(!access(file_name, R_OK)){ //check access
        freopen(file_name, "r", stdin); // replace the stdin with the file
    }*/
    ejecucionComandos(argvs);
    dup2(1,STDIN_FILENO);
    break;
  case 2:
    change_stdout(file_name);
    ejecucionComandos(argvs);
    dup2(0,STDOUT_FILENO);
    break;
  default:
    printf("default\n");
    ejecucionComandos(argvs);
    break;
  }
  return;
}

void change_stdout(char file_name[]){
  printf("ch stdout\n");
    int fid=0;
    int flags = 0, permit = 0;
    int stdout_save;
    /*
     * O_WRONLY -> Abierto solo para escritura
     * O_CREAT  -> Si el archivo existe, este flag no tiene efecto, de lo contrario se crea el archivo
     * O_TRUC   -> Si el archivo existe y es un archivo normal, y se abre con exito O_RDWR o O_WRONLY
             su longitud cambia a 0 y el modo y propietario no cambian
     */
    flags = O_WRONLY|O_CREAT|O_TRUNC;
    /*!
    * S_IWUSR   -> Permisos de escritura y lectura y ejecucion
    * S_IRUSR   -> Es equivalente a  ‘(S_IRUSR | S_IWUSR | S_IXUSR)’.
    */
    permit = S_IWUSR|S_IRUSR;

    fid = open(file_name,flags,permit); //!< Establishes the connection between a file and a file descriptor./

    if (fid < 0) {
        perror("Open");
        exit(1);
    }
    close(STDOUT_FILENO);
    stdout_save= dup(fid);
    //printf("fd: %d\n",stdout_save);
    if (stdout_save<0) {
        perror("dup");
        exit(1);
    }
    close(fid);
  return;
}

void change_stdin(char file_name[]){
  printf("ch stdin\n");
    int flags = 0, permit = 0,fid = 0;
    flags = O_RDONLY;
    permit = S_IWUSR|S_IRUSR;

    close(STDIN_FILENO);
    fid = open(file_name,flags,permit);
    if (fid<0) {
        perror("Open");
        exit(1);
    }
    if (dup(fid)<0) {
        perror("dup");
        exit(1);
    }
    close(fid);
  return;
}