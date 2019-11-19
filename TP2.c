
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



char* hostname(char* buffer2);
void directorio(void);
void comprobar(char* argvs[]);
void separarBuffer(char* buffer);
void minusculas(char* buffer);
void clear_shell(void);
void print_buffer(char* argvs[]);
int tiene_ampercent(char* argvs[]);
void quitar_ultimo(char* argvs[]);
void change_stdout(char file_name[]);
void change_stdin(char file_name[]);
int check_redirection(char* argv[],char file_name[]);
int check_bachfile(char* argv[],char buffer[]);
void ejecucionComandos(char* argvs[]);
void ejecucionComandos_Externos(char file_name[],char buffer[]);

void cut(char* list[], int index);
void comprobar_pato(char* argvs[]);
int check_redirection_pato(char* argv[],char file_name[]);

int fid = 0;
char cwd[PATH_MAX];
int flag_quit=1;
int main (int argc, char* argv[]){
  //printf("%s %s\n",argv[1],argv[2]);
  char buffer2[20];
  char nombre[20];
  strcpy(nombre,hostname(buffer2));
  char buffer[1000];
  char hostname[32];
    gethostname(hostname,32);
    char* user;
    user = getlogin();
    char file_name[20];
    if(check_bachfile(argv,buffer)){
      return 0;
    }
  while(flag_quit){
    printf("%s@%s>> ",user,hostname);
    directorio();
    //printf("%s", buffer);
    if(fgets(buffer,1000,stdin)){
      //minusculas(buffer);
      separarBuffer(buffer);
      printf("final\n");
      //system(buffer); 
      strcpy(buffer,"");
    }
    else{
      printf("fid: %i\n", fid);
      return 1; //lo puse porque cuando hacia el cambio de stdin imprimia el prompt en bucle
            //proba sacarlo y fijate
    }
  }
  return 0;
}
void ejecucionComandos(char* argvs[]){
  if(strcmp(argvs[0],"cd")==0)
  {
    if(strcmp(argvs[1],"..")==0){
      if(chdir("..")==0){
        printf("Se cambio\n");
      }
      else{
        printf("Error\n");
      }
    }
    else{
      if(chdir(argvs[1])==0){
        printf("Se cambio a %s\n",argvs[1]);
      }
      else{
        printf("Error, direccion no valida\n");
      }
    }
  }else if(strcmp(argvs[0],"clr")==0){
    clear_shell();
  }else if(strcmp(argvs[0],"echo")==0){
    print_buffer(argvs);
  }else if(strcmp(argvs[0],"quit")==0){
    flag_quit=0;
  }
  else{
    pid_t pid;
    int status;
    //char* argumentos[] = {"/bin/ls",NULL};
    pid = fork();
    switch(pid){
      case -1:
        perror("Error en fork");
        break;
      case 0:
        if(tiene_ampercent(argvs)){
          printf("tiene\n\n");
          quitar_ultimo(argvs);
        }       
        execvp(argvs[0],argvs);
          //no deberia llegar aca:
        printf("Comando invalido o no existe el programa \n");
        exit(1);
        break;
      default:
        if(tiene_ampercent(argvs) == 0){
        waitpid(pid, &status, 0);
        }
        break;
    }
  }
  return;
}
void separarBuffer(char* buffer){
   char s[] = " \n\t ";
   char* argvs[20];
   int i=1;
   argvs[0] = strtok(buffer, s);
   if(argvs[0] != NULL){
      while( argvs[i-1] != NULL) {
        argvs[i] = strtok(NULL,s);
        i++;
      }
    }
    //separarTabs(argvs);
   //comprobar(argvs);
   printf("a compr\n");
   comprobar_pato(argvs);
   return;
}
void minusculas(char* buffer){
  for(int i = 0;buffer[i] != '\0';++i){
    buffer[i]=tolower(buffer[i]);
  }
  //printf("%s\n",buffer);
  return;
}

char* hostname (char* buffer2){
  FILE* archivo;
  archivo = fopen("/proc/sys/kernel/hostname","r");
  int i,j,k;
  while(fgets(buffer2,20,archivo)){ //Imprime hasta que se termine archivo
    //return buffer;
    //fprintf(stdout,"%s",buffer);
    break;
  }
  j=strlen(buffer2);
  k=' ';
  for(i=0;i<j;i++){
    if(buffer2[i]=='\n'){
      buffer2[i]=k;
    }
  }
  fclose(archivo);
  return buffer2;
}

void directorio(void) {
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("%s$ ", cwd);
   } else {
       perror("getcwd() error");
       return;
   }
   return;
}

void clear_shell(void){
  fprintf(stdout, "\33[2J");
  fprintf(stdout, "\33[1;1H"); // Posiciona el cursor en la primera columna
  return;
}

void print_buffer(char* argvs[]){
  int i = 1;
  while(argvs[i] != NULL){
    printf("%s ", argvs[i]);
    i++;
  }
  printf("\n");
  return;
}

int tiene_ampercent(char* argvs[]){
  int tiene_amp = 0;
  int i = 0;
  while(argvs[i] != NULL){
    i++;
  }
  //printf("tiene %i ", strcmp(argvs[i-1], "&"));
  if(strcmp(argvs[i-1], "&")==0){
    tiene_amp = 1;
  }
  return tiene_amp;
}

void quitar_ultimo(char* argvs[]){
  int i = 0;
  char* argvs2[20];
  while(argvs[i] != NULL){
    i++;
  }
  argvs[i-1] = NULL;
  return;
}

int check_redirection(char* argv[],char file_name[]){
    int i = 0;
    for (i;i<64;i++) {
        if (argv[i] == NULL) {
            file_name = NULL;
            return 0;
        }

        else if (!strcmp(argv[i],"<")) {
            strcpy(file_name,argv[i+1]);
            argv[i] = NULL;
            argv[i+1] = NULL;
            return 1;
        }
        else if (!strcmp(argv[i],">")) {
            strcpy(file_name,argv[i+1]);
            argv[i] = NULL;
            argv[i+1] = NULL;
            return 2;
        }
    }
    return 0;
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
    fid=0;
    int flags = 0, permit = 0;
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
int check_bachfile(char* argv[],char buffer[]){
    if(argv[1] != NULL){
      FILE* batchfile = fopen(argv[1],"r");
      while(fgets(buffer,100,batchfile)){ //Imprime hasta que se termine archivo
      separarBuffer(buffer);
    }   
    return 1;
    }
    return 0;
}

void cut(char* list[], int index){
  printf("cut init %i\n", index);
  int i = index;
  while(list[i] != NULL){
    list[i] = list[i+1];
    i++;
  }
  printf("argv despues de cut: \n");
  print_buffer(list);
  return;
}

/* 
  return 0 : no redirection
  return 1 : input redirection
  return 2 : output redirection
  corta de la listas los "<" y ">" y los nombres de los archivos de redireccion
  devuelve los archivos de redireccion en file_name
*/
int check_redirection_pato(char* argv[],char file_name[]){
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

void comprobar_pato(char* argvs[]){ //acordar de vaciar buffer despues de cada comando
  char file_name[256];
  char buffer_secundario[1000];
  printf("a check red\n");
  int redir = check_redirection_pato(argvs, file_name);
  switch (redir)
  {
  case 1:
    change_stdin(file_name);
    ejecucionComandos(argvs);
    dup2(fid,STDIN_FILENO);
    break;
  case 2:
        if(!access(file_name, R_OK)){ //check access
          freopen(file_name, "r", stdin); // replace the stdin with the file
         }
    //change_stdout(file_name);
    ejecucionComandos(argvs);
      dup2(fid,STDOUT_FILENO);
    break;
  default:
    printf("default\n");
    ejecucionComandos(argvs);
    break;
  }
  return;
}