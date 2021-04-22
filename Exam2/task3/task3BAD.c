#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>

void* fun1(void* x){
    return (void*) ((int)x + 10);
}

void* fun2(void* x){
    return (void*) ((int)x + 20);
}

void* fun3(void* x){
    return (void*) ((int)x + 30);
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Only give the program one int\n");
        return 1;
    }
    pthread_t threads[3];
    int rc;
    void* num;
    

    if((rc = pthread_create(&threads[0], NULL, fun1, (void*)atoi(argv[1])))){
        printf("Thread 1 failed!");
        return 1;
    }

    pthread_join(threads[0], &num);//We must was for thread 1 to complete


    if((rc = pthread_create(&threads[1], NULL, fun2, (void*)num))){
        printf("Thread 2 failed\n");
        return 2;
    }
    
    pthread_join(threads[1], &num);//We must was for thread 1 to complete
    
    if((rc=pthread_create(&threads[2], NULL, fun3, (void*)num))){
        printf("Thread 3 failed!\n");
        return 3;
    }

    pthread_join(threads[2], &num);//We must was for thread 1 to complete

    printf("The thre thread's calculation result is: %d\n", (int)num);

    pthread_exit(NULL);
    return 0;
}
