#include<stdio.h> // Standard output
#include<stdlib.h> // Standard library
#include<unistd.h> // read, write
#include<fcntl.h> // open
#include<sys/stat.h>

#define BUFF 32 // Read one byte at a time

int main (int argc, char** argv){
    //Create a buffer for the reading
    char buf[BUFF];
    //Name of file to read
    char inFileName[] = "foo";
    //Name of file to write to
    char outFileName[] = "clone2";

    //Holds the value that the read function returns
    int readOutput;
    //Runs through every read
    
    //Open read file
    int in = open(inFileName, O_RDONLY);
    //Makes sure that there were no errors opening the reading file
    if(in == -1){
        puts("Error openning read file");
        return 1;
    }
    //Open write file 
    umask(0);
    int out = open(outFileName, O_WRONLY|O_CREAT, 0770);
    //Check if there is an error openning the output file
    if(out == -1){
        puts("Error opening output file");
        close(in);
        return 2;
    }

    while((readOutput=read(in, buf, BUFF) > 0)){
        if(write(out, buf, readOutput) == -1){// Try writing and if error exit
            printf("Writing error!\n");
            return 3;
        }    
    }
    close(in);
    close(out);
    if(readOutput == -1){
        printf("Reading error!");
        return 4;
    }
    return 0;
}
