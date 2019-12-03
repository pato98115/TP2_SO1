#ifndef IO_REDIRECTION
#define IO_REDIRECTION

void cambiar_salida(char file_name[]);
void cambiar_entrada(char file_name[]);
void comprobar(char* argvs[]);
int check_redirection(char* argv[],char file_name[]);
void eliminar_texto(char* list[], int index);

#endif
