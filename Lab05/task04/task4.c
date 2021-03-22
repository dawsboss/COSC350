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
    //1:Nc - number of iterations for child
    //2:Np - number of iterations for parent
    //3:Tc - sleep time for child process
    //4:Tp - sleep time for parent process
    if(argc<=4){
        printf("Need 4 arguments!\n");
        return 1;
    }else if(argc>=6){
        printf("No more than 4 arguments");
        return 1;
    }

    //Check to see if the given numbers are numbers
    int i,j;
    for(i=1; i<=4; i++){
        for(j=0;argv[i][j]!='\0'; j++){
            if(argv[i][j]<'0'||argv[i][j]>'9'){
                printf("Arguments not a number!\n");
                return 1;
            }
        }
    }

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
        n=str_to_int(argv[1]);
        sleepT=str_to_int(argv[3]);
        printf("Exec return: %d\n", execlp("./child", "This is a child", argv[1], argv[3], (char *)0));
        break;
    default:
        n=str_to_int(argv[2]);
        sleepT=str_to_int(argv[4]);
        for(; n>0; n--){
            printf("This is the parent | ID: %d\n", pid);
            sleep(sleepT);
        }
        break;
    }
    
    //added to wait
    if(pid != 0){
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);
        if(WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WIFEXITED(stat_val));
        else
            printf("Child terminated adnormally\n");
    }
    exit(0);
}
