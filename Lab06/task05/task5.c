#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>// wait

void catch(int sig){
    return;
}

int main(){
    int i;
    sigset_t intMask, og_intMask;
    sigset_t quitMask, og_quitMask;

    sigemptyset(&intMask);
    sigemptyset(&quitMask);
    sigaddset(&intMask, SIGINT);
    sigaddset(&quitMask, SIGQUIT);

    //Block SIGINT | SIGQUIT
    sigprocmask(SIG_BLOCK, &intMask, &og_intMask);
    sigprocmask(SIG_BLOCK, &quitMask, &og_quitMask);

    for(i=0; i<5; i++){
        printf("%d\n", i);
        sleep(1);
    }

    signal(SIGQUIT, &catch);//if there was a SIGQUIT inputted, catch it
    sigprocmask(SIG_SETMASK, &og_quitMask, NULL);
    signal(SIGQUIT, SIG_DFL);

    for(i=0; i<5; i++){
        printf("%d\n", i);
        sleep(1);
    }
    
    return(0);
}

