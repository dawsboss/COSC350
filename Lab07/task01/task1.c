#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define NUM_THREADS 2

void* fact(void* n){
    int fac,i;
    fac=1;
    for(i=(int)n; i>1; i--){
        fac*=i;
    }
    return (void*)fac;
    //printf("Fact of %d is %d\n",(int)n,fac);
}

void* add(void* n){
    int fac, i;
    fac=0;
    for(i=(int)n; i>0; i--){
        fac+=i;
    }
    return (void*)fac;
    //printf("Sum of %d is %d\n",(int)n,fac);
}

int main(int argc, char** argv){
    if(argc!=2){
        printf("Enter one integer!\n");
        return 2;
    }
    pthread_t sumThread, facThread;
    int i, rc;
    for(i=0; i<NUM_THREADS; i++){
        printf("IN main: creating thread %d\n", i);
        if(i==0){
            rc = pthread_create(&sumThread, NULL, fact, (void*)atoi(argv[1]));
        }else if(i==1){
            rc = pthread_create(&facThread, NULL, add, (void*)atoi(argv[1]));
        }
    }
    void* sum;
    void* prod;

    pthread_join(sumThread, &sum);
    pthread_join(facThread, &prod);

    printf("input: %d | fact: %d | sum: %d\n", atoi(argv[1]), (int)sum, (int)prod);

    pthread_exit(NULL);
    return 0;
}
