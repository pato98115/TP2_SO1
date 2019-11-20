#ifndef IO_REDIRECTION
#define IO_REDIRECTION

void change_stdout(char file_name[]);
void change_stdin(char file_name[]);
void comprobar(char* argvs[]);
int check_redirection(char* argv[],char file_name[]);

#endif