#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>

#define LEN 20

int* scores = NULL;

void* popScores(void* x){
    int i, in, j, len;
    printf("Input up to 20 test scores and -1 if done before 20: \n");
    for(i=0; i<LEN; i++){
        scanf("%d", &in);
        //printf("Scan: %d\n", in);
        while(in < -1){
            printf("Invalid Entry, Retry!\n");
            scanf("%d", &in);
        }
        if(i == 0){
            //printf("if 1: %d\n", i);
            scores = malloc(1*sizeof(int));
            scores[0] = in;
            len = 0;
        }else{
            //printf("Else 1: i:%d | len: %d\n", i, len);
            int* tmp = malloc((len) * sizeof(int));
            for(j=0; j<len; j++){
                tmp[j] = scores[j];
                //printf("%d", tmp[j]);
            }
            //printf("\n");
            free(scores);
            scores = malloc((len+1) * sizeof(int));
            for(j=0; j<len; j++)
                scores[j] = tmp[j];
            scores[len] = in;
            free(tmp);
        }
        len++;
        if(in == -1){
            for(j=0; scores[j]!=-1&&i<LEN; j++){
                printf("%d ", scores[j]);
            }
            printf("\n");
            pthread_exit(NULL);
        }
    }
    for(i=0; i<LEN; i++){
        printf("%d ", scores[i]);
    }
    printf("\n");
    pthread_exit(NULL);
}


void* avgmed(void* x){
    //calc average
    int i;
    float median=0, sum=0.0;
    for(i=0; scores[i]!=-1&&i<LEN; i++){
        sum += scores[i];
    }
    if(i==0){
        printf("Average and Median are zero!\n");
        pthread_exit(NULL);
    }
    
    float avg = (float)sum/i;

    //Calc median

    //Sort for med
    int len = ++i, mv, j, hold;
    int* tmp = malloc((len-1)*sizeof(int));
    for(i=0; i<len-1; i++){
        tmp[i] = scores[i];
    }
    for(i=0; i<len-1; i++){
        for(j=0; j<len-i-1; j++){
            if(tmp[j] > tmp[j+1]){
                hold = tmp[j];
                tmp[j] = tmp[j+1];
                tmp[j+1] = hold;
            }
        }
    }
    
    
    if((len-1)%2 == 1){
        median = tmp[len/2];
    }else{
        float right = tmp[(len/2)-1];
        float left = tmp[(len/2)];
        median = (right + left)/2;
    }
    printf("Average: %2.2f | Median: %2.2f\n", avg, median);
    free(tmp);
    pthread_exit(NULL);
}


void* minmax(void* x){
    int i, min=scores[0], max=scores[0];
    for(i=0; scores[i]!=-1&&i<LEN; i++){
        if(scores[i] < min){
            min = scores[i];
        }
        if(scores[i] > max){
            max = scores[i];
        }
    }
    printf("Min: %d | Max: %d\n", min, max);
    pthread_exit(NULL);
}


void* clearScore(void* x){
    int i;
    for(i=0; scores[i]!=-1 && i<LEN; i++){
        scores[i] = 0;
        printf("%d ",scores[i]);
    }
    if(scores[i+1] == -1){
        scores[i+1] = 0;
        printf("%d", scores[i+1]);
    }
    printf("\n");
    
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[4];
    int rc, i;

    if((rc = pthread_create(&threads[0], NULL, popScores, NULL))){
        printf("Thread 1 failed!");
        return 1;
    }

    pthread_join(threads[0], NULL);//We must was for thread 1 to complete


    if((rc = pthread_create(&threads[1], NULL, avgmed, NULL))){
        printf("Thread 2 failed\n");
        return 2;
    }
    if((rc=pthread_create(&threads[2], NULL, minmax, NULL))){
        printf("Thread 3 failed!\n");
        return 3;
    }

    pthread_join(threads[1], NULL);//Wait for thread 2 
    pthread_join(threads[2], NULL);//Wait for thread 3

    if((rc=pthread_create(&threads[3], NULL, clearScore, NULL))){
        printf("Thread 4 failed!\n");
        return 4;
    }

    pthread_join(threads[3], NULL);//Wait for thread 34 to finish before exting
    
    pthread_exit(NULL);
    free(scores);
    printf("Done\n");
    return 0;
}




