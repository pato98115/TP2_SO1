#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

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
