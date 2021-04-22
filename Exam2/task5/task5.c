#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<signal.h>

void* thrd1(void* x){
    int i;
    for(i=0; 1; i++){
        if(i==10){
            raise(SIGINT);
        }
        sleep(1);
    }
    pthread_exit(NULL);
}


void* thrd2(void* x){
    while(1){
        sleep(1);
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

    pthread_join(threads[0], NULL);//We must was for thread 1 to complete


    if((rc = pthread_create(&threads[1], NULL, thrd2, NULL))){
        printf("Thread 2 failed\n");
        return 2;
    }

    while(1){
        sleep(1);
    }

    pthread_exit(NULL);
    return 0;
}




