#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>// open
#include<string.h>
#include<sys/wait.h>// wait
#include<sys/stat.h>// umask

int main(){
    pid_t pid;

    pid = fork();
    if(pid == 0){//child
//        printf("pid: %d | getpid: %d | getppid: %d\n", pid, getpid(), getppid());
        
        umask(0);
        int out = open("foo", O_WRONLY|O_CREAT, 0666);
        char* message = "Hi mom";
        write(out, message, strlen(message));
        
//        printf("pid: %d | getpid: %d | getppid: %d\n", pid, getpid(), getppid());
    }else{//parrent
//        printf("pid: %d | getpid: %d\n", pid, getpid());
        int status;
        wait(&status);
        int in = open("foo", O_RDONLY);
        char* message = malloc(1);
        int len = 1;
        message[0] = '\0';
        char buf[1];
        while(read(in, buf, 1) > 0){
//            printf("buff: %c | message: %s\n", buf[0], message);
            char* tmp = malloc(len);
            strcpy(tmp, message);
            free(message);
            len++;
            message = malloc(len);
            strcpy(message, tmp);
            message[len-2] = buf[0];
        }
        printf("My son said, %s\n", message);

//        printf("pid: %d | getpid: %d\n", pid, getpid());
    }
    exit(0);



}

