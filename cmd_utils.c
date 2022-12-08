#include "cmd_utils.h"
#include "exec.h"

void parse_command(char* command){
    command = strtok(command, " ");
    
    if(strcmp(command, "cd\n") == 0 || strcmp(command, "cd") == 0){
        command = strtok(NULL, " ");
        change_dir(command);
    }else if(strcmp(command, "clear") == 0 || strcmp(command, "clr") == 0){
        clear();
    }else if(strcmp(command, "echo\n") == 0 || strcmp(command, "echo") == 0){
        command = strtok(NULL, " ");
	echo(command);
    }else if(strcmp(command, "quit") == 0 || strcmp(command, "q") == 0 || strcmp(command, "exit") == 0){
        printf("See you soon!\n");
        free(command);
        exit(EXIT_SUCCESS);
    }else if(strcmp(command, "help") == 0 || strcmp(command, "h") == 0){
        print_help();
    }else{
        fork_process(command);
    }

    return; 
}


void clear(){printf("\033[H\033[J");}


void echo(char* second_part){
    char* token = NULL;
    
    if(second_part[0]=='$'){
        token = strtok(second_part, "$");
        if(getenv(token) != NULL){
            printf("%s\n", getenv(token));
        }else{
            printf("That environment variable has no matching value\n");
            return;
        }
    }
    else{
        printf("%s\n", second_part);  
    }
}


void change_dir(char* command){
    if(strcmp(command, "") == 0){printf("%s\n", getenv("PWD"));}
    
    else if(strcmp(command, "-") == 0){
        char *aux = NULL; 
        aux = malloc(strlen(getenv("PWD")) + 1);
        strcpy(aux, getenv("PWD"));
        setenv("PWD", getenv("OLDPWD"), 1);
        change_dir(getenv("PWD"));
        setenv("OLDPWD", aux, 1);
        free(aux);
	}

    else{
        char *s = NULL;
        char *aux = NULL; 
        aux = malloc(strlen(getenv("PWD"))+strlen(getenv("OLDPWD"))+1);
        s = malloc(strlen(getenv("PWD"))+strlen(getenv("OLDPWD"))+1);
        strcpy(aux, getenv("PWD"));

	if(chdir(command) == 0){
		setenv("PWD", getcwd(s, 1024), 1);
            	setenv("OLDPWD", aux, 1);
        }else{
            	printf("error: %s\n", strerror(errno));
        }

        free(aux);
        free(s);
    }
}


void print_help(void){
    printf("The list of commands supported by this shell is: %s, %s, %s and %s.\n", "cd", "clr", "echo", "quit");
    printf("In additional, you can also specify the name of a program to run.\n");
    printf("Thanks for using the Crow Shell!\n");
}


int find_pipe(char* command){
    char* aux   =   NULL;
    aux = malloc(strlen(command)+1);
    strcpy(aux, command);

    strtok(aux, " ");

    while(aux != NULL){
      if(strcmp(aux, "|") == 0){;
        return 1;
      }
        aux = strtok(NULL, " ");
    }

    free(aux);
    return 0;
}

/* int find_pipe(char* command){
    while(command != NULL){
        if(*command == '|'){return 1;};
        command++;
    }
    return 0;
} */

int find_redirection(char* command){
    char* aux   =   NULL;
    aux = malloc(strlen(command)+1);
    strcpy(aux, command);

    strtok(aux, " ");

    while(aux != NULL){
      if(strcmp(aux, ">") == 0 || strcmp(aux, "<") == 0){;
        return 1;
      }
        aux = strtok(NULL, " ");
    }

    free(aux);
    return 0;
}
