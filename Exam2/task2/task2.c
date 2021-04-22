#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define STRLEN 256//PLeanty for 2 ints and a \0 char

int main(int argc, char** argv){
   char comand[] = "./anyinput\0"; 
    char buf[STRLEN];
    int num1, num2;
    FILE* filePtr;

    memset(buf, '\0', sizeof(buf));

    if((filePtr=popen(comand, "r")) != NULL){
        while(fgets(buf, STRLEN, filePtr) != NULL){
            if(sscanf(buf, "%d%d", &num1, &num2) == 2){
                sprintf(buf, "The numbers multiplied is: %d\n", num1*num2);
                if(write(STDOUT_FILENO, buf, strlen(buf)) != strlen(buf)){
                    printf("Error writing\n");
                    exit(2);
                }
            }else{
                printf("invalid inputs: two integers\n");
                continue;
            }
        }
    }
    pclose(filePtr);
    
    
    
    exit(0);
}




