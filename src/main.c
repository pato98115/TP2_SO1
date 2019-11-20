
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
void separarBuffer(char* buffer);
void minusculas(char* buffer);

void cut(char* list[], int index);

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
      //minusculas(buffer);
      separarBuffer(buffer);
      printf("final\n");
      strcpy(buffer,"");
    }
    else{
      return 1; //lo puse porque cuando hacia el cambio de stdin imprimia el prompt en bucle
            //proba sacarlo y fijate
    }
  }
  return 0;
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
   printf("a compr\n");
   if(argvs[0]==NULL){
   		return;
   }
   comprobar(argvs);
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
