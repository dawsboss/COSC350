#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>


int main(int argc, char** argv){

    pid_t pid;
    char* message;
    int sleepTime = 1;

    pid = fork();
    switch(pid)
    {
    case -1:
        printf("Fork failed parrent\n");
        exit(1);
    case 0:
        ;
        pid_t pid2;
        pid2 = fork();
        if(pid2 == -1){
            printf("Fork failed child\n");
            _exit(2);
        
        }else if(pid2 != 0){
            message = "I am your child";
            int printAmount = 3;
            for(; printAmount>0; printAmount--){
                puts(message);
                sleep(sleepTime);
            }
            exit(0);
        }else if(pid2 == 0){//Grandchild
            message = "I am your grandchild";
            int tmp = getppid();
            while(getppid() == tmp){
                puts(message);
                sleep(sleepTime);
            }
            _exit(0);
        } 
        break;
    default:
        message = "I am your parent";
        int stat;
        while(waitpid(pid, &stat, WNOHANG) == 0){
            puts(message);
            sleep(sleepTime);
        }
        exit(0);
    }
    exit(0);
    
    //added to wait
   /* if(pid != 0){
        int stat_val;
        pid_t child_pid;
        
        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);
        if(WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WIFEXITED(stat_val));
        else
            printf("Child terminated adnormally");

    }
*/    
    
 //   exit(0);

}
