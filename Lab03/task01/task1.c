#include<stdio.h> // Standard output
#include<stdlib.h> // Standard library
#include<unistd.h> // File

#define BUFF 1 // Read one byte at a time

int main (int argc, char** argv){
    //Create a buffer for the reading
    char buf[BUFF];
    //Name of file to read
    char inFileName[] = "./foo";
    //Name of file to write to
    char outFileName[] = "./clone";

    //Holds the value that the read function returns
    int readOutput;
    //Runs through every read
    while((readOutput=read(0, buf, BUFF) > 0)){
        if(write(1, buf, readOutput) == -1){// Try writing and if error exit
            return 1;
        }    
    }
    if(readOutput == -1){
        printf("Reading error!");
        return 2;
    }
    return 0;
}
