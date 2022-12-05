#ifndef sig_handlers
#define sig_handlers

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
        
void set_sigtstp();
void sigtstp_handler(int);
void set_sigquit();
void sigquit_handler(int);



#endif