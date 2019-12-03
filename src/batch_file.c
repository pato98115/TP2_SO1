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
#include<batch_file.h>
#include<IO_redirection.h>

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
  return;
}