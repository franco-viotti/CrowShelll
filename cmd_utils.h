#ifndef cmd_utils
#define cmd_utils

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define NULL ((void *)0)


void parse_command(char*);
void clear(void);
void echo(char*);
void change_dir(char*);
void print_help(void);
void wait_for_signal(void);
int find_pipe(char*);
int find_redirection(char*);


#endif