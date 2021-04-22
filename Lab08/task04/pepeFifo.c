#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

#define READ 0
#define WRITE 1

/*
 * mkfifo /tmp/task4_fifo --mode=0666
 * Or you could have used mkfifo in the program and made itbbefore executing the rest of the program
 */

int main(){
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];

    memset(buffer, '\0', sizeof(buffer));


    if((file_pipes[READ] = open("/tmp/task4_fifo", O_NONBLOCK, O_RDONLY)) == -1){
        printf("Error opening fifo read\n");
        exit(EXIT_FAILURE);
    }
    if((file_pipes[WRITE] = open("/tmp/task4_fifo", O_WRONLY, O_NONBLOCK))==-1){
        printf("Error opening fifo write\n");
        exit(EXIT_FAILURE);
    }
    
    
    data_processed = write(file_pipes[WRITE], some_data, strlen(some_data));
    printf("Wrote %d bytes\n", data_processed);
    data_processed = read(file_pipes[READ], buffer, BUFSIZ);
    printf("Read %d bytes: %s\n", data_processed, buffer);
    close(file_pipes[WRITE]);
    close(file_pipes[READ]);
    exit(EXIT_SUCCESS);
}

