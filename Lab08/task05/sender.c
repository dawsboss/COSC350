#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<errno.h>
#include "header.h"
#include<signal.h>
#include<unistd.h>

#define BUF 80

int end = 1;

void catch(int sig){
    puts("REE");
    end = 0;
    return;
}

int main(int argc, char** argv){
    int shmid;
    char buf[BUF];
    key_t key;
    struct Memory *shm;
    //Data 
    int numb1, numb2;

    key = ftok(".", 'x');
    if((shmid = shmget(key, sizeof(struct Memory), 0))<0){
        perror("shmget error\n");
        exit(1);
    }
    shm = (struct Memory*) shmat(shmid, NULL, 0);
    if((long)shm == -1){
        perror("shmat error\n");
        exit(1);
    }
    int in;
    shm->gostop = GO;
    shm->status = NOT_READY;
    printf("Enter two integers: \n");
    while((in = read(0, buf, BUF))>0){
        //signal(SIGINT, catch);
        //signal(SIGSTOP, catch);
        //shm->status = NOT_READY;
        /*if{
            printf("REeEeE\n");
            break;
        }*/
        if(sscanf(buf, "%d%d", &numb1, &numb2) == 2){
            shm->nums.num1=numb1;
            shm->nums.num2=numb2;
            shm->status = FILLED;
            while(shm->status != TAKEN)
                ;
            printf("Data is taken by other process\n");
            printf("Enter two integers: \n");
            memset(buf, '\0', BUF);
        }else{
            printf("Invalid input. Input must be two integers!\n");
            printf("Enter two integers: \n");
            memset(buf, '\0', BUF);
            continue;
        }
    }
    shm->gostop = STOP;
    shmdt((void*) shm);
    return 0;
}

