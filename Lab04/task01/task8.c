#include<stdio.h> // Standard output
#include<stdlib.h> // Standard library
#include<unistd.h> // read, write
#include<fcntl.h> // open
#include<sys/stat.h> // umask

#define BUFF 1 // Read one byte at a time

int main (int argc, char** argv){
    //
    //First file should be reading file
    //Second file is the writing to file
    //
    //Checks to see if we have the right amount of inputs
    if(argc<=2){
        printf("Need to have 2 file names inputed\n");
        return 1;
    }else if(argc>3){
        printf("Only pass in two file names\n");
        return 1;
    }
    
    
    
    
    
    //Create a buffer for the reading
    char buf[BUFF];

    //Holds the value that the read function returns
    int readOutput;
    //Open read file to read
    int in = open(argv[1], O_RDONLY);
    //Makes sure that there were no errors opening the reading file
    if(in == -1){
        puts("Error openning read file");
        return 1;
    }
    //Open write file
    umask(0);
    int out = open(argv[2], O_WRONLY|O_CREAT, 0660);
    //Check if there is an error openning the output file
    if(out == -1){
        puts("Error opening output file");
        close(in);
        close(out);
        return 2;
    }
    int done = 0;
    int i; // Itter for inner for loop
    int num;
    char strBuff[4];
    strBuff[0]=' ';
    while((readOutput=read(in, buf, BUFF) > 0)){
         num = *buf - '\0';
         for(i=3; i>=1; i--){
             strBuff[i] = (num%10) + '0';
             num/=10;
         }
         /*num = (*buf-'\0');
         if(num<=32 || num>126){
             char space[1];
             space[0] = ' ';             
             if(write(out, space, 1) == -1){
                printf("Writing error in file!\n");
                return 3;
             }
         }else*/
         if(write(out, strBuff, 4) == -1){
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
