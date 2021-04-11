#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define STRLEN 80//PLeanty for 2 ints and a \0 char

int main(int argc, char** argv){
    int i, j, size=0;
    char* comand;
    for(i=1; i<argc; i++){
        size+=strlen(argv[i]);
    }

    comand = malloc(size*sizeof(char));

    for(i=1; i<argc; i++){
        sprintf(comand, "%s %s", comand, argv[i]);
    }

    char buf[BUFSIZ];
    FILE* filePtr;

    if((filePtr=popen(comand, "r")) != NULL){
        while(fgets(buf, BUFSIZ, filePtr) != NULL){
            (void)printf("%s",buf);
        }
    }
    pclose(filePtr);
    
    
    
    exit(0);
}




