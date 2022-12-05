//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "cmd_utils.h"
#include "sig_handlers.h"
#include "exec.h"
#include "redirectIO.h"

//DEFINES
#define MAX_LIMIT 100
#define CCYN  "\x1B[36m"
#define CNRM  "\x1B[0m"
#define CGRN  "\x1B[32m"

//GLOBAL VARIABLES
sigjmp_buf  sigint_buf;

//FUNCTION DECLARATIONS
void print_pwd(void);
void print_user(void);
void print_host(void);
void read_script(char*); 
void sigint_handler(int signal);
void set_sigint(void);


int main(int argc, char **argv){

    char* command;
    command = (char*) malloc(sizeof(char)*1024);
    size_t buffer = 0;

    set_sigint();
    set_sigtstp();
    set_sigquit();

    clear();

    if(argc > 1){
        read_script(argv[1]);
    }else{
        while(1){
            print_user();
            print_host();
            print_pwd();

            //Check if getline function is successful. Prevent segmention fault with empty commands
            if(getline(&command, &buffer, stdin) == -1 || *command == '\n'){
                printf("Your command is empty or erroneous. Try again!\n");
            }
            else{
                command[strcspn(command, "\n")] = '\000'; //Character \n is deleted
                if(find_pipe(command)){
                    mypipe(command);
                }
                else if(find_redirection(command)){
                    redirect(command);
                }
                else{
                    parse_command(command);
                }
            }
        } 
    }   

    free(command);
    return 0;
}


void print_pwd(void){
    printf( "%s%s", CGRN, getenv("PWD") );
    printf(" >%s ", CNRM);
    
    return;
}


void print_user(void){
    char* user = getenv("USER");
    printf("%s%s", CCYN, user);

    return; 
}


void print_host(void){
    char output[100];
    gethostname(output, sizeof(output));
    printf("@%s:%s~", output, CNRM);

    return;
}


void read_script(char *file){
    FILE* fpointer;
    fpointer = fopen(file,"r");
    char* buffer = NULL;
    buffer = malloc(300);

    if(fpointer == NULL){
        printf("Error: Could not open file %s.\nError number: %d\n",file, errno);
    }else{
        while(fgets(buffer, 300, fpointer) != NULL){
            buffer[strcspn(buffer, "\n")] = '\000';
            if(strcmp(buffer, "") != 0){    
                parse_command(buffer);
            }
        }
        fclose(fpointer);
    }

    free(buffer);
    return;
}


void sigint_handler(int signal){
    siglongjmp(sigint_buf, 1);
}


void set_sigint(void){
    signal(SIGINT, sigint_handler);
    if(!sigsetjmp(sigint_buf, 1));
    else;
}

