#include<stdio.h> // Standard Output
#include<stdlib.h> // Standard Library
#include<unistd.h> // read, write
#include<fcntl.h> // open
#include<sys/stat.h> // umask
#include<string.h> // String Library

#define BUFF 1


/**************************************************
 Convert integer to string    
 Params: x is the int to be converted,
 str is the string into which to writeReturns: length of the string
**************************************************/
int convIntToStr(char* str, int x){
    sprintf(str, "%d", x);
    return (strlen(str));
}

int main(int argc, char** argv){
    if(argc!=2){
        printf("Need one file input!\n");
        return 1;
    }
    
    char buf[BUFF]; // Reading in buffer
    
    
    // problem says max of 80 bytes of data
    char holder[80]; // Holds all read in values
    
    
    int in = open(argv[1], O_RDONLY);
    
    if(in == -1){
        printf("Error opening file!\n");
        return 2;
    }
    
    int readIn; // file handler

    int i = 0; // itter
    while((readIn=read(in, buf, BUFF)) > 0 && i<80){
        printf("I: %d | buf: %c\n",i, buf[0]);
        holder[i]=buf[0];
        i++;
    }
    printf("ans: %s\n", holder);
    close(in);
}
