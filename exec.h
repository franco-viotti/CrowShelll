#ifndef exec
#define exec

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>


void fork_process(char*);
void exec_process(char**);
char** get_args(char*);
int mypipe(char*);



#endif