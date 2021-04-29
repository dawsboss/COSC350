#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/msg.h>

typedef struct MSGBUF{
    long type;
    int one, two;
}MsgBuf;

int main(int argc, char** argv){
    key_t key;
    if((key = ftok("msgQsnd.c", 'B')) == -1){
        perror("ftok() error");
        exit(1);
    }
    int Qid;
    if((Qid = msgget(key, 0644 | IPC_CREAT)) == -1){
        perror("msgget() error");
        exit(2);
    }

    MsgBuf buf;
    while(1){
        if(msgrcv(Qid, (MsgBuf*) &buf, 2*sizeof(int), 0, 0) == -1){
            perror("msgrcv() error");
            exit(3);
        }
        printf("The sum is %d\n", buf.one + buf.two);
    }
    exit(0);
}


