#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>

int main(int argc, char** argv){
    srand(time(NULL));
    if(argc != 2){
        printf("incorrect cal: ./task2 {a positive number}\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if(n<0){
        printf("Given varriable must be even!\n");
        return 2;
    }else if(n==0){
        printf("Your string is empty\n");
        return 0;
    }

    char* string = malloc(n*sizeof(char) + 1);
    int i=0;
    while(n>0){
        string[i] = rand()%26 + 'a';
        n--;
        i++;
    }
    string[i]='\0';
    printf("Your string is: %s\n", string);
    free(string);
    return 0;
}
