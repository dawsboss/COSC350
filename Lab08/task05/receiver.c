#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<errno.h>
#include"header.h"

int main(int argc, char** argv){
    int shmid, n, int1, int2;
    key_t key;
    struct Memory *shm;
    key = ftok(".", 'x');
    if((shmid = shmget(key, sizeof(struct Memory), 0))<0){
        perror("shmget error\n");
        exit(1);
    }
    shm = (struct Memory*) shmat(shmid, NULL, 0);
    if((long)shm == -1){
        perror("shmget error\n");
        exit(1);
    }
    while(shm->gostop == GO){
        while(shm->status != FILLED){
            if(shm->gostop == STOP)
                break;
            ;
        }
        printf("The sum of %d and %d = %d\n", shm->nums.num1, shm->nums.num2, shm->nums.num1+shm->nums.num2);
        shm->status = TAKEN;
    }
    shmdt((void*) shm);
    return 0;
}

