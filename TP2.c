#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<ctype.h>

char* hostname(char* buffer2);
void directorio(void);
void comprobar(char* argvs[]);
void separarBuffer(char* buffer);
void minusculas(char* buffer);

char cwd[PATH_MAX];

int main (void){
	char buffer2[20];
	char nombre[20];
	strcpy(nombre,hostname(buffer2));
	char buffer[1000];
 	char hostname[32];
    gethostname(hostname,32);
    char* user;
    user = getlogin();

	while(1){
		printf("%s@%s>> ",user,hostname);
		directorio();
		fgets(buffer,1000,stdin);
		//minusculas(buffer);
		separarBuffer(buffer);
		//system(buffer);	
	}
	return 0;
}
void comprobar(char* argvs[]){ //acordar de vaciar buffer despues de cada comando
	if(strcmp(argvs[0],"cd")==0)
	{
		if(strcmp(argvs[1],"..")==0){
			if(chdir("..")==0){
				printf("Se cambio\n");
				}
			else {
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
		system("clear");
	}else {
		printf("Comando no valido\n");
	}
	return;
}
void separarBuffer(char* buffer){
   char s[] = " \n\t ";
   char* argvs[20];
   int i=1;
   argvs[0] = strtok(buffer, s);
   //argvs[0] = strtok(argvs[0],s2);
   //printf( "%s\n", token);
   printf( "%s\n", argvs[0]);
   //comprobar(token);
   if(argvs[0] != NULL){
   		while( argvs[i-1] != NULL) {
	   		argvs[i] = strtok(NULL,s);
	   		//printf( "%s\n", token);
	   		//printf("%s\n", token);
	   		//comprobar(token);
	   		if(argvs[i]!=NULL){
	   			printf("%s\n",argvs[i]);
	   		}
	   		i++;
   		}
  	}
  	//separarTabs(argvs);
   comprobar(argvs);
   return;
}
void minusculas(char* buffer){
	for(int i = 0;buffer[i] != '\0';++i){
		buffer[i]=tolower(buffer[i]);
	}
	printf("%s\n",buffer);
	return;
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
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("%s$ ", cwd);
   } else {
       perror("getcwd() error");
       return;
   }
   return;
}