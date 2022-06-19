//!!!!! debug--->done

// 2 processes
// 1) child process should take a string input from user
// 2) Parent is going to display the user input
//-----------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char* argv[]){
    int fd[2];
    if(pipe(fd) == -1){
        return 3;
    }

    int pid = fork();
    if(pid == -1){
        return 2;
    }

    if(pid == 0){
        close(fd[0]);
        char arr[5];
        
        printf("enter a string:\n");
        fgets(arr,5,stdin);
        // arr[strlen(arr)-1]='\0';

        int strsize=strlen(arr)+1;
        printf("\n%d\n",strsize);
       
        if(write(fd[1],&strsize,sizeof(int)) == -1){
            return 4;
        }
        
        if(write(fd[1],arr,sizeof(char)*strsize) == -1){
            return 4;
        }
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        char str[5];
        int size;

        if(read(fd[0],&size,sizeof(int))==-1){
        // printf("\nhere\n");
            return 5;
        }
        
        if(read(fd[0],str,sizeof(char)*size)==-1){
            return 5;
        }
        close(fd[0]);
        printf("Received:%s\n",str);
        wait(NULL);
    }
    return 0;
}