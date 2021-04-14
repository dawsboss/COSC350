#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ+1];
    pid_t fork_result;

    memset(buffer, '\0', sizeof(buffer));

    if(pipe(file_pipes) == 0){
        fork_result = fork();
        if(fork_result == -1){
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }

        if(fork_result == 0){//Child
            close(file_pipes[0]);
            sprintf(buffer, "%d", file_pipes[1]);
            (void)execl("pipe4V2", "pipe4V2", buffer, some_data, (char*)0);
            exit(EXIT_FAILURE);
        }else{//Parrent
            close(file_pipes[1]);
            wait(&fork_result);
            data_processed = read(file_pipes[0], buffer, BUFSIZ);
            printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
            close(file_pipes[0]);
        }
    }
    exit(EXIT_SUCCESS);
}



