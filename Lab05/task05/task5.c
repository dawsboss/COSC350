#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

#define BUFF 1

/*
 * This code differs from task2 because not parent will wait
 * for the child to finish executing bfefore terminating it's
 * self. This makes sure that the child terminates and also in
 * this case fixed the bug where the child would print over
 * the user's console
*/


int main(int argc, char** argv){
    //argv[i]
    //1: File name/location
    if(argc!=2){
        printf("Need one argument, file name\n");
        return 1;
    }

    pid_t pid;

    //Open the file for both child and parent
    int openDes = open(argv[1], O_RDONLY);
    if(openDes == -1){
        printf("Error opening given file\n");
        return 1;
    }
    char buf[BUFF];
    int cOffset = 0;
    int pOffset = 0;
    int in;
    char space[1];
    space[0] = ' ';

    pid = fork();
    switch(pid)
    {
    case -1:
        printf("Fork failed\n");
        exit(1);
    case 0://This is the child code
        ;//C is buggy

        int childTXT = open("child.txt", O_WRONLY | O_CREAT, 0666);
        if(childTXT == -1){
            printf("Error opening child.txt\n");
            _exit(1);
        }
        while((in = pread(openDes, buf, BUFF, cOffset))>0){
            if(in == -1){
                printf("Error reading in child\n");
                _exit(2);
            }
            cOffset++;
            if(buf[0]<'0' || buf[0]>'9'){
                if(write(childTXT, buf, BUFF) == -1){
                    printf("Error writing in child\n");
                   _exit(3);
                }
            }else if(buf[0] == '\n'){
                if(write(childTXT, buf, BUFF) == -1){
                    printf("Error writing in child new line\n");
                    _exit(4);
                }
            }else{
                if(write(childTXT, space, 1) == -1){
                    printf("Error writing in child space\n");
                   _exit(5);
                }
            }
        }

        _exit(0);
    default://This is the parent code
        ;//c blows, delceration isn;t statment

        int parentTXT = open("parent.txt",O_WRONLY | O_CREAT, 0666);
        if(parentTXT == -1){
            printf("Error opening parent.txt\n");
            return 1;
        }

        while((in=pread(openDes, buf, BUFF, pOffset))>0){
            if(in == -1){
                printf("Error reading in parent\n");
                return 1;
            }
            pOffset++;
            if(buf[0]>'0' && buf[0]<'9'){
                if(write(parentTXT, buf, BUFF) == -1){
                    printf("Error writing in parent\n");
                    return 1;
                }
            }else if(buf[0] == '\n'){
                if(write(parentTXT, buf, BUFF) == -1){
                    printf("Error writing in parent new line\n");
                    return 1;
                }
            }else{
                if(write(parentTXT, space, 1) == -1){
                    printf("Error writing in parent space\n");
                    return 1;
                }
            }
        }

        break;
    }
    
    //added to wait
    /*if(pid != 0){
        int stat_val;
        pid_t child_pid;
        
        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);
        if(WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WIFEXITED(stat_val));
        else
            printf("Child terminated adnormally");

    }*/
    
    
    exit(0);

}
