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
    buf.type = 1;
    char* input = (char*) calloc(256, sizeof(int));

    printf("Input two ints\n");

    while(fgets(input, 256, stdin), !feof(stdin)){
        if(sscanf(input, "%d%d", &buf.one, &buf.two) != 2){
            printf("Enter two ints\n");
            continue;
        }
        if(msgsnd(Qid, (MsgBuf*) &buf, 2*sizeof(int), 0) == -1){
            perror("msgsnd() error");
            exit(3);
        }
        printf("Enter two ints\n");
    }

    if(msgctl(Qid, IPC_RMID, NULL) == -1){\
        perror("msgctl() error");
        exit(4);
    }
    exit(0);
}
