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
void change_stdout(char file_name[]);
void change_stdin(char file_name[]);
int check_redirection(char* argv[],char file_name[]);
int check_backfile(char* argv[],char buffer[]);
void ejecucionComandos(char* argvs[]);
void ejecucionComandos_Externos(char file_name[],char buffer[]);

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
    if(check_backfile(argv,buffer)){
    	return 0;
    }
	while(flag_quit){
		printf("%s@%s>> ",user,hostname);
		directorio();
		if(fgets(buffer,1000,stdin)){
			//minusculas(buffer);
			separarBuffer(buffer);
			//system(buffer);	
			strcpy(buffer,"");
		}
	}
	return 0;
}
void comprobar(char* argvs[]){ //acordar de vaciar buffer despues de cada comando
	char file_name[256];
	char buffer_secundario[1000];
	if(check_redirection(argvs,file_name)==2){
		change_stdout(file_name);
		ejecucionComandos(argvs);
		//printf("fileno: %d\n",dup(STDOUT_FILENO));
    	dup2(fid,STDOUT_FILENO); //Esto lo que hace es volver a reestrablecer los fd para que vuelva a consola
    	//printf("fd ahora: %d\n",stdout_save);
    	//printf("fd fileno ahora: %d\n",STDOUT_FILENO);
		//dup2(fid,1); 
	}else if(check_redirection(argvs,file_name)==1){ //Esto hay que revisar para que funcione
		change_stdin(file_name);
		if(check_redirection(argvs,file_name)==2){
			change_stdout(file_name);
		}
		printf("aca :D\n");
		ejecucionComandos_Externos(file_name,buffer_secundario);
		dup2(fid,STDIN_FILENO);
	}else{
		ejecucionComandos(argvs);
		printf("check: %d\n",check_redirection(argvs,file_name));
	}
	//ejecucionComandos(argvs);
	return;
}
void ejecucionComandos_Externos(char file_name[],char buffer[]){ //Esto es nuevo, es supuestamente para que ejecute los comandos
    FILE* batchfile = fopen(file_name,"r");
    while(fgets(buffer,100,batchfile)){ //Imprime hasta que se termine archivo
		separarBuffer(buffer);
	}		
	return;
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
				//printf("Soy el hijo: %d, mi padre es %d\n",getpid(),getppid());				
				execvp(argvs[0],argvs);
					//no deberia llegar aca:
				printf("Comando invalido o no existe el programa \n");
				exit(1);
				break;
			default:
				wait(&pid);
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
}

void change_stdin(char file_name[]){
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
}
int check_backfile(char* argv[],char buffer[]){
    if(argv[1] != NULL){
    	FILE* batchfile = fopen(argv[1],"r");
    	while(fgets(buffer,100,batchfile)){ //Imprime hasta que se termine archivo
			separarBuffer(buffer);
		}		
		return 1;
    }
    return 0;
}