#include<stdio.h>
#include<unistd.h>
#include<signal.h>

/*
 * D. The hold in the bakcgroudn and call kill is done on line 12.
 *      This will take the given signal and diflkect it back to the sender.
 *      Somehting else that will also achieve the same result would be using
 *      the sigaction struct and adding the flad SA_RESETHAND this both sends
 *      it to the background and then after the first run of the signal and 
 *      then resets the signal to it's default.
 */ 

void ouch(int sig){
    printf("OUCH! - I got signal %d\n", sig);
    (void) signal(SIGINT, SIG_DFL);//part D answer and E
}

int main(){
    struct sigaction act;

    act.sa_handler = ouch;
    sigemptyset(&act.sa_mask);
    //act.sa_flags = SA_RESETHAND; This is an aswer for part E

    sigaction(SIGINT, &act, 0);

    while(1){
        printf("Hello World!\n");
        sleep(1);
    }
}
