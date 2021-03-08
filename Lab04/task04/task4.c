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
    strcat(dir12, "/Dir2/Dir12");
    strcpy(helloCpy, dir12);
    strcat(helloCpy, "/hello");

    printf("home: %s\ndir1: %s\ndir2: %s\ndir12: %s\n",home, dir1, dir2, dir12);
    if( (mkdir(dir1, 0775) > 0)||(mkdir(dir2, 0775))||(mkdir(dir12, 0775))){
        printf("Error creating dir\n");
        return 1;
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
    return 0;
}
