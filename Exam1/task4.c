#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>


#define BUFF 1

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
    if(argc<6){
        printf("To few argumentsgiven, need five file names!\n");
        return 1;
    }else if(argc>6){
	      printf("No more than five file input!\n");
				return 1;
		}
		
		umask(0);

		int in = open(argv[1], O_RDONLY);
		if(in == -1){
			  printf("Error oppening file!i First argument should be the input! \n");
				return 2;
		}
		int alpha = open(argv[2], O_RDWR|O_CREAT, 0666);
		if(in == -1){
			  printf("Error opening file! \n");
				return 2;
		}
		int num = open(argv[3], O_RDWR|O_CREAT, 0666);
		if(in == -1){
			  printf("Error opening file! \n");
				return 2;
		}
		int other = open(argv[4],  O_RDWR|O_CREAT, 0666);
		if(in == -1){
			  printf("Error opening file! \n");
				return 2;
		}
		int copy = open(argv[5], O_RDWR|O_CREAT, 0666);
		if(in == -1){
			  printf("Error opening file! \n");
				return 2;
		}


		char buf[BUFF];//for reading
		int readOutput;//hold file reading

		int size=0;
		char s[1];
		s[0]=' ';

		while((readOutput=read(in, buf, BUFF)) > 0){
				size++;
				if(buf[0] == '\n'){
					  if(write(alpha, buf, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
					 	if(write(num, buf, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
					 	if(write(other, buf, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
				}else if(buf[0]>='0' && buf[0]<='9'){
						if(write(num, buf, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
						if(write(alpha, s, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
						if(write(other, s, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
				}else if((buf[0]>='a' && buf[0]<='z')  ||  (buf[0]>='A' && buf[0]<='Z')){
						if(write(alpha, buf, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
						if(write(num, s, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
						if(write(other, s, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
				}else{
						if(write(other, buf, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
						if(write(num, s, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}
						if(write(alpha, s, readOutput)==-1){
								printf("Error writing!\n");
								return 3;
						}

				}
		}


		close(in);

		if(readOutput == -1){
				printf("Reading error!\n");
				return 4;
		}
    
		int i,j,k;
		char* buffer1 = malloc(size);
		char* buffer2 = malloc(size);
		char* buffer3 = malloc(size);

		/*close(alpha);
		close(other);
		close(num);
		
		alpha = open(argv[2], O_RDONLY, 0666);
		if(in == -1){
			  printf("Error opening file! \n");
				return 2;
		}
		num = open(argv[3], O_RDONLY, 0666);
		if(in == -1){
			  printf("Error opening file! \n");
				return 2;
		}
		other = open(argv[4],  O_RDONLY, 0666);
		if(in == -1){
			  printf("Error opening file! \n");
				return 2;
		}*/
    if(lseek(alpha, 0, SEEK_SET) == -1){
        printf("Error lseeking back to begining\n");
        return 1;
    }
    if(lseek(num, 0, SEEK_SET) == -1){
        printf("Error lseeking back to begining\n");
        return 1;
    }
    if(lseek(other, 0, SEEK_SET) == -1){
        printf("Error lseeking back to begining\n");
        return 1;
    }

		i=read(alpha, buffer1, size);
		j=read(num, buffer2, size);
		k=read(other, buffer3, size);
		if(i==-1 || j==-1 || k==-1){
				printf("num, aplha, or other broke reoppening\n i:%d j:%d k:%d\nsize:%d\n",i,j,k,size);
				return 5;
		}
		char copytext[size];
		int w;
		for(w=0; w<size; w++){
				if(buffer2[w]!=' '){
					copytext[w]=buffer2[w];
				}else if(buffer3[w]!=' '){
					copytext[w]=buffer3[w];
				}else{
					copytext[w]=buffer1[w];
				}
		}
		if(write(copy, copytext, size)==-1){
				printf("Error writing copy\n");
				return 6;
		}

		close(alpha);
		close(other);
		close(num);
		close(copy);
		return 0;
}
