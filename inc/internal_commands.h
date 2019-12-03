#ifndef INTERNAL_COMMANDS
#define INTERNAL_COMMANDS

void ejecucionComandos(char* argvs[]);
void borrar_terminal(void);
void quitar_ultimo(char* argvs[]);
void print_buffer(char* argvs[]);


extern int flag_quit;

#endif
