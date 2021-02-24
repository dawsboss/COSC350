#include<stdio.h> // Standard output
#include<stdlib.h> // Standard library
#include<unistd.h> // read, write
#include<fcntl.h> // open
#define BUFF 1 // Read one byte at a time

int main (int argc, char** argv){
    //Create a buffer for the reading
    char buf[BUFF];
    
    if(argc==1){
        printf("Need file name and location in input!\n");
        return 1;
    }

    //Holds the value that the read function returns
    int readOutput;
    //Runs through every read
    
    //Open read file
    int in = open(argv[1], O_RDONLY);
    //Makes sure that there were no errors opening the reading file
    if(in == -1){
        puts("Error openning read file");
        return 1;
    }
    int size=0;
    while((readOutput=read(in, buf, BUFF) > 0)){
        size++;
    }
    close(in);
    if(readOutput == -1){
        printf("Reading error!");
        return 4;
    }
    printf("The size fo the file is %d bytes!\n",size);
    return 0;
}
