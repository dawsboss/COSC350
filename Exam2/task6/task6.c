#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thrd1(void* x){
    while(1){
        if(counter<10){
            pthread_mutex_lock(&mutex);
            counter++;
            printf("counter: %d\n",counter);
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}


void* thrd2(void* x){
    while(1){
        if(counter>0){
            pthread_mutex_lock(&mutex);
            counter--;
            printf("counter: %d\n",counter);
            pthread_mutex_unlock(&mutex);
        }
    }
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[2];
    int rc, i;

    if((rc = pthread_create(&threads[0], NULL, thrd1, NULL))){
        printf("Thread 1 failed!");
        return 1;
    }

    if((rc = pthread_create(&threads[1], NULL, thrd2, NULL))){
        printf("Thread 2 failed\n");
        return 2;
    }
    
    pthread_exit(NULL);
    return 0;
}




