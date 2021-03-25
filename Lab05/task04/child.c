#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

/*
 * This code differs from task2 because not parent will wait
 * for the child to finish executing bfefore terminating it's
 * self. This makes sure that the child terminates and also in
 * this case fixed the bug where the child would print over
 * the user's console
*/

int str_to_int(char* num){
    int i=0;
    int rtn=0;
    while(num[i] != '\0'){
        rtn*=10;
        rtn+=(num[i] - '0');
        i++;
    }
    return rtn;
}

int main(int argc, char** argv){
    //argv[i]
    //0:Message - message to be printed
    //1:Nc - number of iterations for child
    //2:Tc - sleep time for child process
    /*if(argc<=3){
        printf("Need 3 arguments!\n");
        return 1;
    }else if(argc>=5){
        printf("No more than 3 arguments\n");
        return 1;
    }*/

    //Check to see if the given numbers are numbers

    pid_t pid = getpid();
    char* message = argv[0];
    int n=str_to_int(argv[1]);
    int sleepT=str_to_int(argv[2]);
    for(; n>0; n--){
        printf("%s | ID: %d\n", message, pid);
        sleep(sleepT);
    }
    exit(37);

}
