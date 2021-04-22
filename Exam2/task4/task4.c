#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>// open
#include<string.h>
#include<sys/wait.h>// wait
#include<sys/stat.h>// umask

void parrent(int SIG){
    if(SIG == SIGUSR1){
        printf("From now on, I am zombie\n");
    }
    _exit(0);
}
int main(){
    pid_t pid, pid2;
    pid = fork();
    if(pid == 0){//child 1
        signal(SIGUSR1, parrent);
        while(1){
            printf("I am your child\n");
            sleep(1);
        }
        _exit(0);
    }else{//parrent
        int i;
        for(i=0; 1; i++){
            if(i==10){
                kill(pid, SIGUSR1);
            }
            printf("I am your parent\n");
            sleep(1);
        }
    }
    exit(0);
}

