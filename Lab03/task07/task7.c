#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define BUFF 1

int StrtoInt(char* string){//Returns -1 if error
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
    int sum=0;
    for(i=1; i<argc; i++){
        sum+=StrtoInt(argv[i]);
    }
    printf("The sum of the inputs is %d\n", sum);

    return 0;
}
