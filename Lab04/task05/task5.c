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
    len = strlen(argv[1]);
    char* oldPath;
    
    if(argv[2][0]=='~'){
        len+=(strlen(getenv("HOME")) - 2);//Take one for ~ being replced
        newPath = malloc(len);
        strcpy(newPath, getenv("HOME"));
        strcat(newPath, argv[2]);
    }else{
        newPath = malloc(len);
        strcat(newPath, argv[2]);
    }
   
    if(argv[1][0]=='~'){
        len+=(strlen(getenv("HOME")) - 2);//Take one for ~ being replced
        oldPath = malloc(len);
        strcpy(oldPath, getenv("HOME"));
        strcat(oldPath, argv[1]);
    }else{
        oldPath = malloc(len);
        strcat(oldPath, argv[1]);
    }

    printf("oldPath: %s\nnewPath: %s\n", oldPath, newPath);
    //if(access(oldPath, F_OK) < 0){
    //    printf("Can't access given file to move!\n");
    //    return 1;
    //}



    struct stat buf;
    if(stat(argv[2], &buf) < 0){//Either the Directory DOesn;t exits or we need to rename so try rename and if that doesn;t work then directory doesn;t exist
        if(rename(oldPath, newPath) < 0){
            printf("Invalid Desination or Destination does not exist\n");
            return 1;
        }
    }//otherwise There is a directory already so we can move safetly
    
    if(link(oldPath, newPath) < 0){
        printf("Error linking to move\n");
        return 1;
    }
    if(unlink(oldPath) < 0){
        printf("Error unlinking\n");
        return 1;
    }
    




    return 0;
}
