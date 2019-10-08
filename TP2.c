#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<ctype.h>
#include<sys/wait.h>
#include<sys/types.h>


char* hostname(char* buffer2);
void directorio(void);
void comprobar(char* argvs[]);
void separarBuffer(char* buffer);
void minusculas(char* buffer);
void clear_shell(void);

char cwd[PATH_MAX];
int flag_quit=1;

int main (void){
	char buffer2[20];
	char nombre[20];
	strcpy(nombre,hostname(buffer2));
	char buffer[1000];
 	char hostname[32];
    gethostname(hostname,32);
    char* user;
    user = getlogin();

	while(flag_quit){
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
		clear_shell();
	}else if(strcmp(argvs[0],"quit")==0){
		flag_quit=0;
	}else if(strcmp(argvs[0],"shell")==0){
		pid_t pid;
		int status;
		//char* argumentos[] = {"/bin/ls",NULL};
		pid = fork();
		switch(pid){
			case -1:
				perror("Error en fork");
				break;
			case 0:
				printf("Soy el hijo: %d, mi padre es %d\n",getpid(),getppid());
				//execl("/bin/echo","echo","Hello,World",NULL);
				execv(argumentos[0],argumentos);
				break;
			default:
				/*while(wait(&status) != pid){
					if(status == 0){
						printf("Ejecucion normal del hijo\n");
					}else{
						printf("Error del hijo\n");
					}
				}*/
				wait(NULL);
				printf("padre: %d, my hijo es %d\n",getpid(),pid);
				break;
		}
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

void clear_shell(void){

fprintf(stdout, "\33[2J”");
fprintf(stdout, "\33[1;1H"); // Posiciona el cursor en la primera columna

}
