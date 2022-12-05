#ifndef redirectIO
#define redirectIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "cmd_utils.h"

#define NULL ((void *)0)


int redirect(char*);
void IO_handler(FILE*, FILE*);
char* get_next_word(char*);
char* get_command(char*);


#endif