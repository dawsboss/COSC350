#include<stdio.h> // Standard output
#include<stdlib.h> // Standard library
#include<unistd.h> // read, write
#include<fcntl.h> // open
#include<sys/stat.h> // umask

#define BUFF 1 // Read one byte at a time

int main (int argc, char** argv){
    //Create a buffer for the reading
    char buf[BUFF];
    //Name of file to read 1
    char inFileName[] = "foo";
    //Name of file to write to
    char outFileName[] = "foorev";

    //Holds the value that the read function returns
    int readOutput;
    //Runs through every read
    
    //Open read file 1
    int in = open(inFileName, O_RDONLY);
    //Makes sure that there were no errors opening the reading file
    if(in == -1){
        puts("Error openning read file");
        return 1;
    }
    //Open write file
    umask(0);
    int out = open(outFileName, O_WRONLY|O_CREAT, 0760);
    //Check if there is an error openning the output file
    if(out == -1){
        puts("Error opening output file");
        close(in);
        close(out);
        return 2;
    }
    int done = 0;
    int counter = 0;
    int length=0;
    //int counter=lseek(in, -1, SEEK_END);
    while((readOutput=pread(in, buf, BUFF, counter) > 0) && done==0){
        length++;
        counter++;
    }
    length--;
    counter = 0;
    while((readOutput=pread(in, buf, BUFF, counter) > 0) && done==0){
        if(pwrite(out, buf, readOutput, length-counter) == -1){// Try writing and if error exit
            printf("Writing error in file!\n");
            return 3;
        }
        counter+=1;
    }
    close(in);
    close(out);
    if(readOutput == -1){
        printf("Reading error!");
        return 4;
    }
    return 0;
}
