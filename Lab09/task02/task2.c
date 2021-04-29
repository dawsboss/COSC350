#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/msg.h>
#include<pthread.h>

/*
 *  Without tools we do not know what thread is accessing what
 *  I would like to use mutex but this is suppose to show
 *  why we need to use mutex/semaphore. With this program
 *  there is no guarentee what is is going to happen. The two
 *  threads with desync form one another in that the couters
 *  will write over top of one another. If the counter is
 *  wrong then we run into the issues of using invalid
 *  numbers as the recently sent number in the array.
 *
 */

#define BUFSIZE 10

int count = 0;
int list[BUFSIZE];

void* producer(void* x){
    int item = rand() % 10;
    while(1){
        item = rand() % 10;
        if(count >= BUFSIZE){
            sleep(1);
            continue;
        }
        printf("Sending: %d\n", item);
        list[count++] = item;//insert_item(item);  count+=1;
    }
}

void* consumer(void* x){
    int item;
    while(1){
        if(count < 0){
            sleep(1);
            continue;
        }
        printf("Revieving: %d\n", item);
        item = list[count--];//item = remove_item();  count-=1;
    }
}


int main(int argc, char** argv){
    pthread_t T[2];
    int rc1, rc2;

    rc1 = pthread_create(&T[0], NULL, producer, NULL);
    rc2 = pthread_create(&T[1], NULL, consumer, NULL);

    pthread_join(T[0], NULL);
    pthread_join(T[1], NULL);
    exit(0);
}
