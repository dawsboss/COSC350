#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>

#define READ 0  //In the file_pipes this one will be the read desc
#define WRITE 1 //In the file_pipes this one will be the write desc

int main(){
    int data_processed;
    int file_pipe1[2];//Parrent to Child
    int file_pipe2[2];//Child to Parrent
    const char some_data[] = "Hi there kiddo";
    char buffer1[BUFSIZ+1];//Sends pipe1 file des
    char buffer2[BUFSIZ+1];//Sends pipe2 file des
    char buffer[BUFSIZ+1];//Holds read in message
    pid_t fork_result;

    memset(buffer1, '\0', sizeof(buffer1));
    memset(buffer2, '\0', sizeof(buffer2));
    memset(buffer, '\0', sizeof(buffer));


    if(pipe(file_pipe1) != 0){
        printf("Pipe1 failed\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(file_pipe2) != 0){
        printf("Pipe2 failed\n");
        exit(EXIT_FAILURE);
    }
    
    fork_result = fork();
    if(fork_result == -1){
        fprintf(stderr, "Fork failure");
        exit(EXIT_FAILURE);
    }

    if(fork_result == 0){//Child
        close(file_pipe1[WRITE]);
        close(file_pipe2[READ]);
        sprintf(buffer1, "%d", file_pipe1[READ]);
        sprintf(buffer2, "%d", file_pipe2[WRITE]);
        (void)execl("pipe4", "pipe4", buffer1, buffer2, "Hi, Mom\0", (char*)0);
        exit(EXIT_FAILURE);
    }else{//Parrent
        close(file_pipe1[READ]);
        close(file_pipe2[WRITE]);
        data_processed = write(file_pipe1[WRITE], some_data, strlen(some_data));
        printf("%d - wrote %d bytes\n", getpid(), data_processed);
        wait(&fork_result);
        data_processed = read(file_pipe2[READ], buffer, BUFSIZ);
        printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
    }


    exit(EXIT_SUCCESS);
}



