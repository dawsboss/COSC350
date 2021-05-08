#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>// open
#include<string.h>
#include<sys/wait.h>// wait
#include<sys/stat.h>// umask
#include<sys/types.h>

#define BUF 7
#define BUF2 16

void parrent(int SIG){
    return;
}
int main(){
    //Create pipe
    int fd[2];
    pipe(fd);

    //
    pid_t pid;
    pid = fork();
    if(pid == 0){//child 1
        int out = open("foo", O_WRONLY|O_CREAT,"0777");
        write(out, "Hi, Mom", BUF);
        kill(getppid(), SIGUSR1);
        char buff[BUF2+1];
        buff[BUF2] = '\0';
        read(fd[0], buff, BUF2);
        printf("My mom said, %s\n", buff);
        close(out);
        close(fd[0]);
        kill(getppid(), SIGUSR1);
        _exit(0);
    }else{//parrent
        signal(SIGUSR1, parrent);
        pause();
        int in = open("foo", O_RDONLY);
        char buf[BUF+1];
        buf[BUF] = '\0';
        read(in, buf, BUF);
        printf("My son said, %s\n", buf);
        char buf2[BUF2] = "What do you want";
        write(fd[1], buf2, BUF2);
        signal(SIGUSR1, parrent);
        pause();
        close(in);
        close(fd[1]);
        _exit(0);
    }
    exit(0);
    return(0);
}

