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
#include<background_execution.h>

int flag_quit=1;

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

void clear_shell(void){
  fprintf(stdout, "\33[2J");
  fprintf(stdout, "\33[1;1H"); // Posiciona el cursor en la primera columna
  return;
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


void print_buffer(char* argvs[]){
  int i = 1;
  while(argvs[i] != NULL){
    printf("%s ", argvs[i]);
    i++;
  }
  printf("\n");
  return;
}
