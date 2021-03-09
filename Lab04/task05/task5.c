#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>

#define BUFF 1

int main(int argc, char** argv){
    if(argc<3 || argc>3){
        printf("Incorrect call, expected: ./task4 file destination\n");
        return 1;
    }

    int len = strlen(argv[2]);
    char* newPath; 
    
        

    struct stat buf;
    if(stat(argv[2], &buf) < 0){
        printf("Invalid Desination or Destination does not exist\n");
        return 1;
    }


    if(argv[2][0]=='~'){
        len+=(strlen(getenv("HOME")) - 1);//Take one for ~ being replced
        newPath = malloc(len);
        strcpy(newPath, getenv("HOME"));
        strcat(newPath, argv[2]);
    }else{
        newPath = malloc(len);
        strcat(newPath, argv[2]);
    }


    if(S_ISREG(buf.st_mode)){
        
    }else{
    
    }

    
    return 0;
}
