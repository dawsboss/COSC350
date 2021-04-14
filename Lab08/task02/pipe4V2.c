#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char** argv){
    int data_processed;
    char buffer[BUFSIZ+1];
    int file_descriptor;

    memset(buffer, '\0', sizeof(buffer));
    sscanf(argv[1], "%d", &file_descriptor);
    sscanf(argv[2], "%s", buffer);
    data_processed = write(file_descriptor, buffer, strlen(buffer));
    close(file_descriptor);
    printf("%d - wrote %d bytes\n", getpid(), data_processed);
    exit(EXIT_SUCCESS);
}
