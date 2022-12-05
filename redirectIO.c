#include "redirectIO.h"

int redirect(char* command){
    char* aux_I = strchr(command, '<'); 
    char* aux_O = strchr(command, '>'); 
   
    if (aux_I!=NULL || aux_O!=NULL){
        int fds_input[2];
        int fds_output[2];

        pid_t pid;
        pipe(fds_input);
        pipe(fds_output);
        pid = fork();

        if(pid==-1)
            printf("%s", strerror(errno));
        else if (pid==0){
        close(fds_input[1]);

        if (aux_I!=NULL)   
            dup2(fds_input[0], STDIN_FILENO);

        close(fds_input[0]);
        close(fds_output[0]);

        if (aux_O!=NULL)
            dup2(fds_output[1], STDOUT_FILENO);

        close(fds_output[1]);

        command=get_command(command);
        parse_command(command);
        free(command);
        exit(0);
        }
        else{
            pid=fork();

            if(pid==0){
                close(fds_input[0]);
                if (aux_I!=NULL) {      
                    FILE *stream1;
                
                    stream1=fdopen(fds_input[1], "w");
                    char *file_input=get_next_word(aux_I);
                    FILE *file1= fopen(file_input,"r"); 
                
                    IO_handler(file1, stream1); 
                }
                close(fds_input[1]);
                close(fds_output[1]);

                if (aux_O!=NULL){
                    FILE *stream2;
                    stream2=fdopen(fds_output[0], "r");
                    char *file_output=get_next_word(aux_O);
                    FILE *file2= fopen(file_output,"w"); 
                    IO_handler(stream2, file2);
                }

                close(fds_output[0]);
                exit(0);
            }
            
            close(fds_input[0]);
            close(fds_input[1]);
            close(fds_output[0]);
            close(fds_output[1]);
            wait(0);
            wait(0);
            return 1;
        }
    }
    return 0; 
}

void IO_handler(FILE* read, FILE* written){
    if(written == NULL)
        printf("%s", strerror(errno));
    else{
        char *temp= (char*) malloc(sizeof(char)*512);
    
        while(fgets(temp, 512,read) != NULL){
            fputs(temp,written);
        }

        fflush(read);
        fclose(written);
        free(temp);
    }
}

char *get_command(char* command){
    char *temp=(char *)calloc(1024,sizeof(char));

    for(int i=0; command[i]!='<'&&command[i]!='>'; i++){
        temp[i]=command[i];
    }

   return temp;
}

char *get_next_word(char* file){
   file++;
   file=strtok(file, " ");
   return file;
}

