#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char** argv){
    
    pid_t pid;
    char* message;
    int sleepT, n;
    printf("For program starting\n");
    pid = fork();
    switch(pid)
    {
    case -1:
        printf("Fork failed\n");
        exit(1);
    case 0:
        message = "This is a child";
        n=5;
        break;
    default:
        message = "This is the parent";
        n=3;
        break;
    }
    for(; n>0; n--){
        puts(message);
        sleep(1);
    }

    exit(0);
}
