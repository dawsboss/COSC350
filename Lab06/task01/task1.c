#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>


static int alarm_fired = 0;

void ding(int sig){
    alarm_fired = 1;
}

int main(){
    pid_t pid;
    struct sigaction act;
    act.sa_handler = ding;

    printf("Alarm testing\n");

    pid = fork();
    if(pid == -1){
        printf("Fork failed\n");
        exit(1);
    }else if(pid == 0){
        sleep(5);
        kill(getppid(), SIGALRM);
        exit(0);
    }

    printf("Waiting for alarm to go off\n");
    sigaction(SIGALRM, &act, NULL);//(void) signal(SIGALRM, ding);

    pause();

    if(alarm_fired)
        printf("Ding!\n");
    printf("done\n");
    exit(0);
}


