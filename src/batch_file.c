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