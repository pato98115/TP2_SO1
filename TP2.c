#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>

char* hostname(char* buffer2);
void directorio(void);

int main (void){
	char buffer2[20];
	char nombre[20];
	strcpy(nombre,hostname(buffer2));
	while(1){
		char buffer[1000];
		printf("%s: ",nombre);
		scanf("%s",buffer);
		system(buffer);
		directorio();
	}
	return 0;
}
char* hostname (char* buffer2){
	FILE* archivo;
	archivo = fopen("/proc/sys/kernel/hostname","r");
	int i,j,k;
	while(!feof(archivo)){ //Imprime hasta que se termine archivo
		fgets(buffer2,20,archivo);
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
   char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   } else {
       perror("getcwd() error");
       return;
   }
   return;
}