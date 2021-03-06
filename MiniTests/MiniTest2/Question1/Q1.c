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
    char outFileName[] = "symmetry";

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
    int out = open(outFileName, O_WRONLY|O_CREAT, 0600);
    //Check if there is an error openning the output file
    if(out == -1){
        puts("Error opening output file");
        close(in);
        close(out);
        return 2;
    }
    int done = 0;
    int counter=lseek(in, -1, SEEK_END);
    while((readOutput=read(in, buf, BUFF) > 0) && done==0){
        if(write(out, buf, readOutput) == -1){// Try writing and if error exit
            printf("Writing error in file!\n");
            return 3;
        }
        if(counter==0){
            counter=lseek(in, 0, SEEK_SET);
            done = 1;
        }else{
            counter=lseek(in, -2, SEEK_CUR);
        }
    }
    char space[4];
    space[0]=' ';
    space[1]='|';
    space[2]='|';
    space[3]=' ';
    if(write(out, space, 4) == -1){
        printf("Writing error om file!");
        return 3; 
    }
    lseek(in,0,SEEK_SET);
    while((readOutput=read(in, buf, BUFF)) > 0){
        if(write(out, buf, readOutput)==-1){
            printf("Writing error in file!\n");
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
