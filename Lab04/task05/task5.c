#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>

#define BUFF 1

int main(int argc, char** argv){
    if(argc<3 || argc>3){
        printf("Incorrect call, expected: ./task4 file destination\n");
        return 1;
    }

    char newPath[strlen(argv[2])];
    strcpy(newPath, argv[2]);
   
    struct stat buf;
    if(stat(argv[1], &buf) == -1){
        printf("First parameter file does not exists\n");
        return 1;
    }
    if(!S_ISREG(buf.st_mode)){
        printf("First aprameter is not a file");
        return 1;
    }

    if(stat(argv[2], &buf) == -1){//Either the directory doesn't exits or we need to rename
        if(rename(argv[1], newPath) < 0){
            printf("Invalid Desination or Destination does not exist\n");
            return 1;
        }
    }else{//otherwise There is a directory already so we can move safetly
        if(S_ISREG(buf.st_mode)){
            printf("Already a file there named that!\n");
            return 1;
        }
            int len=(strlen(argv[1])+strlen(argv[2]));
            int addSlash = 0;
            int dotSlash = 0;
            char G[1];
            G[0] = '/';
            

            if(argv[2][strlen(argv[2])-1] != '/'){
                len++;
                addSlash = 1;
            }
            char nPath[len];

            strcpy(nPath, newPath);

            if(addSlash==1){
                strcat(nPath, G);
            }
            
            int i;
            int j=0;
            int length=0;
            for(i=strlen(argv[1])-1; i>=0; i--){
                if(argv[1][i] == '/')
                    break;
                length++;
            }

            int end = length;
            char tmp[length+1];
            for(i=strlen(argv[1])-1; i>=0; i--){
                if(argv[1][i] == '/'){
                    tmp[j]='\0';
                    break;
                }
                tmp[j]=argv[1][i];
                j++;
            }
            tmp[j]='\0';
            char fileName[end];
            j=0;
            for(i=end - 1; i>=0; i--){
                fileName[j] = tmp[i];
                j++;
            }
            fileName[j]='\0';
            strcat(nPath, fileName);

            if(link(argv[1], nPath) < 0){
                printf("File already exisists\n");
                return 1;
            }
            if(unlink(argv[1]) < 0){
                printf("Error unlinking\n");
                return 1;
            }
        //}

    }
    

    return 0;
}
