#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>

#define BUFF 1

int main(int argc, char** argv){
    
    int len = (strlen(getenv("HOME")) + 1);
    char* home = malloc(len*sizeof(char));
    char* dir1 = malloc(len+5);
    char* dir2 = malloc(len+5);
    char* dir12 = malloc(len+10);
    char* helloCpy = malloc(len+10+6);

    strcpy(home, getenv("HOME"));
    strcpy(dir1, home);
    strcpy(dir2, home);
    strcpy(dir12, home);

    strcat(dir1, "/Dir1");
    strcat(dir2, "/Dir2");
    strcat(dir12, "/Dir2/Dir21");
    strcpy(helloCpy, dir12);
    strcat(helloCpy, "/hello");

    //printf("home: %s\ndir1: %s\ndir2: %s\ndir12: %s\n",home, dir1, dir2, dir12);
    //Do we need to make?
    struct stat buff;
    if(stat(dir1, &buff)<0){
        if(mkdir(dir1, 0775) < 0){
            printf("Error creating Dir1\n");
            return 1;
        }
    }
    if(stat(dir2, &buff) < 0){
        if(mkdir(dir2, 0775) < 0){
            printf("Error creating Dir2\n");
            return 1;
        }
    }
    if(stat(dir12, &buff) < 0){
        if(mkdir(dir12, 0775) < 0){
            printf("Error creating Dir21\n");
            return 1;
        }
    }

    int cpy = open(helloCpy, O_WRONLY|O_CREAT, 0777);
    if(cpy==-1){
        printf("Error opening out file\n");
        return 1;
    }
    int in = open("hello", O_RDONLY);
    if(in == -1){
        printf("Error opening in file\n");
        return 1;
    }
    int readOut;
    char buf[BUFF];
    while((readOut=read(in, buf, BUFF)) > 0){
        if(write(cpy, buf, readOut) == -1){
            printf("Error writing\n");
            return 1;
        }
    }
    if(readOut==-1){
        printf("Error reading\n");
        return 1;
    }
    close(cpy);

    //linking
    char* toHello = malloc(len+5+8);
    strcpy(toHello, dir1);
    strcat(toHello, "/toHello");

    char* toDir21 = malloc(len+5+8);
    strcpy(toDir21, dir1);
    strcat(toDir21, "/toDir21");


    if(stat(toHello, &buff)<0){
        if(symlink(helloCpy, toHello) < 0){
            printf("Error symlink toHello!\n");
            return 1;
        }
    }

    if(stat(toDir21, &buff)<0){
        if(symlink(dir12, toDir21) < 0){
            printf("\n");
            return 1;
        }
    }

    return 0;
}
