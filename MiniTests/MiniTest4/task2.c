#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>// open
#include<string.h>
#include<sys/wait.h>// wait
#include<sys/stat.h>// umask
#include<pthread.h>


void ogMsg(){
    printf("The original thread job is done\n");
    _exit(0);
}

void thread1Msg(void* x){
    printf("The first thread job is done\n");
    pthread_cancel((pthread_t) x);//Cancel main thread
    pthread_exit(NULL);
}

void* thread1(void* x){
    int old;
    pthread_setcancelstate(PTHREAD_CANCEL_DEFERRED, &old);
    while(1){
        printf("This is the first thread\n");
        pthread_testcancel();
        sleep(1);
    }
}
void* thread2(void* x){
    int i;
    for(i=0; i<10; i++){
        printf("This is the second thread\n");
        sleep(1);
    }
    printf("The second thread job is done\n");
    pthread_cancel((pthread_t) x);//Cancel thread1
    pthread_exit(NULL);
}



int main(){
    pthread_t thr1, thr2;
    int rc=0;

    pthread_t og = pthread_self();

    if((rc=pthread_create(&thr1, NULL, thread1, (void*) og)) != 0){
        printf("Error creating thread1\n");
        exit(rc);
    }
    if((rc=pthread_create(&thr2, NULL, thread2, (void*) thr1)) != 0){
        printf("Error creating thread2\n");
        exit(rc);
    }
    while(1){
        printf("This is the original\n");
        pthread_testcancel();
        sleep(1);
    }
    
    exit(0);
}

