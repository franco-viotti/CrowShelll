#include "sig_handlers.h"

void set_sigtstp(){
    signal(SIGTSTP, sigtstp_handler);
}

void sigtstp_handler(int signal){
    return;
}

void set_sigquit(){
    signal(SIGQUIT, sigquit_handler);
}

void sigquit_handler(int signal){

}