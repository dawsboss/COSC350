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
    char inFileName1[] = "foo";
    //Name of file to read 2
    char inFileName2[] = "foo1";
    //Name of file to write to
    char outFileName[] = "foo12";

    //Holds the value that the read function returns
    int readOutput;
    //Runs through every read
    
    //Open read file 1
    int in1 = open(inFileName1, O_RDONLY);
    //Makes sure that there were no errors opening the reading file
    if(in1 == -1){
        puts("Error openning read file");
        return 1;
    }
    //Open read file 2
    int in2 = open(inFileName2, O_RDONLY, 0760);
    if(in2 == -1){
        puts("Error openning read file");
        return 1;
    }
    //Open write file
    umask(0);
    int out = open(outFileName, O_WRONLY|O_CREAT, 0760);
    //Check if there is an error openning the output file
    if(out == -1){
        puts("Error opening output file");
        close(in1);
        close(in2);
        close(out);
        return 2;
    }

    while((readOutput=read(in1, buf, BUFF) > 0)){
        if(write(out, buf, readOutput) == -1){// Try writing and if error exit
            printf("Writing error in file 1!\n");
            return 3;
        }    
    }
    close(in1);
    lseek(out, 0, SEEK_END);
    while((readOutput=read(in2, buf, BUFF) > 0)){
        if(write(out, buf, readOutput) == -1){// Try writing and if error exit
            printf("Writing error in file 2!\n");
            return 3;
        }    
    }
    close(in2);
    close(out);
    if(readOutput == -1){
        printf("Reading error!");
        return 4;
    }
    return 0;
}
