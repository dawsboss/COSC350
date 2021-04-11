#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define STRLEN 80//PLeanty for 2 ints and a \0 char

int main(){
    int fd[2];
    int i, j;
    pid_t pid;

    if(pipe(fd) < 0){
        printf("Pip error!\n");
        exit(1);
    }
    if((pid=fork()) < 0){
        printf("Fork error\n");
        exit(2);
    }
    if(pid > 0){//parrent
        close(fd[0]);
        int in;
        char sline[STRLEN];
        printf("Input two integers: \n");
        while((in = read(STDOUT_FILENO, sline, STRLEN)) > 0){
            write(fd[1], sline, in);
            printf("Input two more ints:\n");
        }
    }else{//child
        close(fd[1]);
        int num1, num2, in;
        char sline[STRLEN];
        while((in=read(fd[0], sline, STRLEN)) > 0){
            if(sscanf(sline, "%d%d", &num1, &num2) == 2){
                sprintf(sline, "The sum is %d\n", num1+num2);
                if(write(STDOUT_FILENO, sline, strlen(sline)) != strlen(sline)){
                    printf("Error writing\n");
                    exit(2);
                }
            }else{
                printf("Invalid input. Input must be two integers!\n");
                continue;
            }
        }
    }

    exit(0);
}




