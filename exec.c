#include "exec.h"
#include "cmd_utils.h"

bool bg_process = false;

void fork_process(char* command){
    int ret, wstatus, w;
    ret = fork();

    char** args = malloc(sizeof(command)*8);
    
    switch (ret) {
        case -1:
            printf("Fork failed. Error code: %d\n", errno);
            exit(1);
        case 0:
            exec_process(get_args(command));
        default:
            args = get_args(command);
            if(!bg_process){
                do { 
                    w = waitpid(ret, &wstatus, WUNTRACED | WCONTINUED);
                    if (w == -1) {
                        perror("waitpid");
                        exit(EXIT_FAILURE);
                    }
                    if (WIFEXITED(wstatus)) {
                        printf("\n");
                    } else if (WIFSIGNALED(wstatus)) {
                        printf("killed by signal %d\n", WTERMSIG(wstatus));
                    } else if (WIFSTOPPED(wstatus)) {
                        printf("stopped by signal %d\n", WSTOPSIG(wstatus));
                    } else if (WIFCONTINUED(wstatus)) {
                        printf("continued\n");
                    }
                    if(WEXITSTATUS(wstatus)==255){
                        printf("invalid command.\n");
                        print_help();
                    }
                } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
            }else{
                printf("[1] %d\n", ret);
            }
            free(args);
            break;
    }
}


void exec_process(char** args){
    if(execvp(args[0], args)!=-1){
    }else{
        free(args);
        exit(-1);
    }
    free(args); //Teoricamente, esta linea nunca se ejecutaria. No estoy seguro de que se libere args.
}


char** get_args(char* command){
    char **args;
    args=(char**)malloc(0);
    
    int i=0;

    while(command!=NULL){
        args = (char **) realloc(args, sizeof(command)); //Array size gets modified upon command size
        if(args == NULL){   
            printf("error trying to reallocate memory\n");
            free(args);
            exit(1);
        }
        args[i]=command; //First element must be, by convention, the program name 
        command = strtok(NULL, " ");
        i++;
    }
    args[i]=NULL; //Last element must be NULL

    if(strcmp(args[i-1], "&") == 0){
        bg_process = true;
    }else{
        bg_process = false;
    }

    return args;
}

int mypipe(char* command){
    int fd[2]; //Declare file descriptors array
    command = strtok(command, "|");

    //Open up a pipe
    if(pipe(fd) == -1){
        printf("%s\n", strerror(errno));
        return 1; //Error
    }

    //First fork, for the stdout
    int pid1 = fork();
    if(pid1 < 0){
        printf("%s\n", strerror(errno));
        return 1; //Error
    }

    if(pid1 == 0){
        //We are in child process No.1 
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        command = strtok(command, " ");
        exec_process(get_args(command));
        
    }   
    //ping google.com -c 4 | grep "rtt"
    //Second fork, for the stdin
    int pid2 = fork();
    if(pid2 < 0){
        printf("%s\n", strerror(errno));
    }
    command = strtok(NULL, "\0");
    if(pid2 == 0){
        //Child process No.2
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);

        command = strtok(command+1, " ");
        exec_process(get_args(command));   
        
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}


