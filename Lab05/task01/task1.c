#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

char* mygetenv(char** envp, char* desiredEnv){//returns -1 if error
    char** d = envp;
    while(*d != NULL){
        char* p = malloc(strlen(*d)+1);
        strcpy(p, *d);
        char* searchWord = strtok(p, "=");
        //printf("input: %s | output: %s\n", desiredEnv, searchWord);
        if(strcmp(searchWord, desiredEnv) == 0){
            char* loc = strchr(*d, '=');
            char* rtn = malloc(strlen(loc)+1);
            strcpy(rtn, loc);
            //printf("Found the word! %s | rtb: %s\n", searchWord, rtn);
            free(p);
            return rtn;
        }
        *d++;
        free(p);
    }
    return NULL;
}


int main(int argc, char** argv, char** envp){
    /*if(argc!=2){
        printf("./task1 {enviroment variables / \"environ\"}\n");
        return 1;
    }*/
    if(envp == NULL){
        printf("envp paraemeter was given empty\n");
        return 2;
    }

    /*char** p = envp;

    while(*p != NULL){
        printf("%s (%p)\n", *p, *p);
        *p++;
    }*/
    char* output = mygetenv(envp, "LS_COLORS");//LS_COLORS is an edge case!
    if(output == NULL){
        printf("Could not find ENVP!\n");
    }else{
        printf("ENVP: %s\n", output);
        free(output);
    }
    exit(0);
}
