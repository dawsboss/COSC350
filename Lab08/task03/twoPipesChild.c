#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char** argv){
    int data_processed;
    char buffer[BUFSIZ+1];
    int file_write, file_read;

    memset(buffer, '\0', sizeof(buffer));
    sscanf(argv[1], "%d", &file_read);
    sscanf(argv[2], "%d", &file_write);
    data_processed = read(file_read, buffer, BUFSIZ);
    printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
    data_processed = write(file_write, argv[3], strlen(argv[3]));
    printf("%d - wrote %d bytes\n", getpid(), data_processed);
    exit(EXIT_SUCCESS);
}
