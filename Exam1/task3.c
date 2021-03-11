#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>


#define BUFF 1
#define numBUFF 80

int str_to_int(char* string){//Returns -1 if error
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

char* int_to_str(int num){
    int j=num;
    int size=0;
    while(j>0){
        size++;
        j/=10;
    }

    char *rtn = malloc(size+1);
    for(j=size-1; j>=0; j--){
        rtn[j] = (num%10) + '0';
        num/=10;
    }
    return rtn;
}

int main(int argc, char** argv){
    if(argc==1){
        printf("Need one file input!\n");
        return 1;
    }else if(argc>2){
        printf("No more than one file input!\n");
        return 1;
    }

    int in = open(argv[1], O_RDONLY);
    if(in == -1){
        printf("Error oppening file!\n");
        return 2;
    }

    char buf[BUFF];//for reading
    char cnum[numBUFF];//For the possible number
    int readOutput;//hold file reading
    int num=0;//hold end number
    int i=0;//Hold what digit the number is

    int j=0;
    int isNum = 0;
    while((readOutput=read(in, buf, BUFF)) > 0){
            if(j>=80){
                break;
            }
            j++;
            if(buf[0]>='0' && buf[0]<='9'){
                    cnum[i]=buf[0];
                    i++;
                    isNum=1;
            }
    }
    if(isNum==0){
        printf("No number in file!\n");
        return 1;
    }
    num = str_to_int(cnum);
    num+=100;

    close(in);
    if(readOutput == -1){
            printf("Reading error!\n");
            return 4;
    }
    int temp=num;
    int size=0;
    while(temp>0){
            size++;
            temp/=10;
    }
    char* rtn = int_to_str(num);
    write(1, rtn, size);
    printf("\n");
    free(rtn);
    return 0;
}
