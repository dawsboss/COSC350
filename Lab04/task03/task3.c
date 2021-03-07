#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>


#define BUFF 1

int palind(int fd1, int fd2){
    char buf1[BUFF];
    char buf2[BUFF];
    //Make sure the files start where the need to be
    //lseek(fd1, 0, SEEK_SET);
    //lseek(fd2, -3, SEEK_END);
    int read1;
    int read2;
    while(( (read1=read(fd1, buf1, BUFF)) > 0 ) && ( (read2=read(fd2, buf2, BUFF)) > 0 )){
        printf("buf1[0]: %c | buf2[0]: %c\n", buf1[0], buf2[0]);
        if(buf1[0]!=buf2[0]){
            return 0;
        }
        lseek(fd2, -2, SEEK_CUR);
    }
    return 1;
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
    int inCopy = dup(in);

    if(palind(in, inCopy)==1){
        printf("File contains a palindrome!\n");
        return 0;
    }else{
        printf("File does NOT contain a palindrome!\n");
        return 0;
    }
    
    
    return 0;
}
