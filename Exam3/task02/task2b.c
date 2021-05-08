#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<errno.h>
#include<sys/msg.h>

#define NOT_READY -1
#define FILLED 0
#define TAKEN 1
#define GO 2
#define STOP 3

struct ints{
    int num1, num2;
};
struct Memory{
    int status;
    int gostop;
    struct ints data;
};




typedef struct MSGBUF{
    long type;
    int one, two;
}MsgBuf;

int main(int argc, char** argv){
    key_t key;
    if((key = ftok(".", 'B')) == -1){
        perror("ftok() error");
        exit(1);
    }
    int Qid;
    if((Qid = msgget(key, 0666 | IPC_CREAT)) == -1){
        perror("msgget() error");
        exit(2);
    }

    key_t key2;
    if((key2 = ftok(".",'B')) == -1){
        perror("ftok error");
        exit(3);
    }
    int shmid;
    if((shmid = shmget(key2, sizeof(struct Memory), IPC_CREAT | 0666)) == -1){
        perror("shmget error");
        exit(4);
    }


    MsgBuf buf;
    struct Memory *shm = (struct Memory*)shmat(shmid, NULL, 0);
    shm->status = NOT_READY;
    shm->gostop = GO;
    while(1){
        if(msgrcv(Qid, (MsgBuf*) &buf, sizeof(buf), 0, 0) == -1){
            break;
        }
        shm->data.num1 = buf.one;
        shm->data.num2 = buf.two;
        shm->status = FILLED;
        while(shm->status != TAKEN)
            ;
        printf("one:%d | two:%d\n", shm->data.num1, shm->data.num2);
    }
    shm->gostop = STOP;
    shmdt((void*)shm);
    exit(0);
}


