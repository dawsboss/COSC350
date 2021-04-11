#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>// open
#include<string.h>
#include<sys/wait.h>// wait
#include<sys/stat.h>// umask

void leaveParrent(int SIG){
    printf("My child is gone so I don't need to stay!\n");
    _exit(0);
}

void leaveChild(int SIG){
    if(SIG == SIGUSR1){
        printf("I am terminated by my parrent\n");
        _exit(0);
    }
}

int main(){
    pid_t pid, pid2;
    pid = fork();
    if(pid == 0){//child 1
        int i;
        while(1){
            printf("Child is running\n");
            sleep(1);
            signal(SIGUSR1, leaveChild);
        }
        _exit(0);
    }else{//parrent
        int i;
        for(i=1; 1; i++){
            printf("Parrent is still running\n");
            sleep(1);
            
            if(i%10 == 0){
                kill(pid, SIGUSR1);
                signal(SIGCHLD, leaveParrent);
                pause();
            }
        }
    }
    return(0);
}

