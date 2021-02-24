#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFF 1

int st_to_int(char* string){//Returns -1 if error
    char str; // Currect string
    int i; // Loop itter
    int neg = 0; // Assume number is positive
    int rtn=0;
    for(i=0; string[i]!='\0'; i++){
        str = string[i];
        if(str=='-' && i==0){//Good negative sign
            neg = 1;
        }else if(str<'0'||str>'9'){//There is a non number entered
            printf("%s is a invalid number!\n", string);
            return -1;
        }else{//Good number to add
            rtn*=10;
            rtn+=(str - '0');
        }
    }
    if(neg==1)
        return -1*rtn;
    return rtn;
}

int main(int argc, char** argv){
    if(argc==1){
        printf("Need to enter atleast 1 integer in!\n");
        return 1;
    }
    int i;
    int sumE=0;
    int sumO=0;
    int curr;
    for(i=1; i<argc; i++){
        curr=st_to_int(argv[i]);
        if(curr%2==0){
            sumE+=curr;
        }else{
            sumO+=curr;
        }
    }
    printf("The sum of the EVEN inputs is %d\n", sumE);
    printf("The sum of the ODD intputs is %d\n",sumO);
    return 0;
}
