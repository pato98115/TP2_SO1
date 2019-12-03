
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
#include<IO_redirection.h>
#include<batch_file.h>
#include<background_execution.h>

char* hostname(char* buffer2);
void directorio(void);
void minusculas(char* buffer);

char cwd[PATH_MAX];

int main (int argc, char* argv[]){
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
    if(fgets(buffer,1000,stdin)){
      minusculas(buffer);
      separarBuffer(buffer);
      strcpy(buffer,"");
    } 
    else{
      return 1; //lo puse porque cuando hacia el cambio de stdin imprimia el prompt en bucle
            //proba sacarlo y fijate
    }
  }
  return 0;
}

char* hostname (char* buffer2){
  FILE* archivo;
  archivo = fopen("/proc/sys/kernel/hostname","r");
  int i,j,k;
  while(fgets(buffer2,20,archivo)){ //Imprime hasta que se termine archivo
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
