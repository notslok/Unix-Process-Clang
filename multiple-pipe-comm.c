#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<time.h>
#include<fcntl.h>

int main(int argc, char* argv[]){
    int fd1[2];//for child->parent pipe
    int fd2[2];//for parent->child pipe
    //[0]->read 
    //[1]->write
    //creating pipes----------------------------
    if(pipe(fd1) == -1){
        printf("Failed to create child to parent pipe!\n");
        return -99;
    }
    if(pipe(fd2) == -1){
        printf("Failed to create parent to child pipe!\n");
        return -99;
    }
    //forking process----------------------------
    
    int id = fork();
    if(id == -1){
        printf("Error while forking process!\n");
        return -2;
    }
    
    //access conditionals------------------------

    if(id == 0){//i.e. child process
        int request;
        close(fd2[1]);
        close(fd1[0]);

        if(read(fd2[0], &request, sizeof(request)) == -1){
            printf("failed to read parent's request from buffer!\n");
            return -3;
        }

        printf("processing request...\n");
        sleep(2);
        
        int response = request*2;
        
        printf("response ready...\n");
        sleep(2);
        
        if(write(fd1[1], &response, sizeof(response)) == -1){
            printf("failed to write response in the buffer!\n");
            return -4;
        }
        sleep(1);
        
        printf("Response sent to parent process...\n");
        close(fd1[1]);
        close(fd2[0]);
    }
    else{
        int request;
        close(fd2[0]);
        close(fd1[1]);

        printf("Enter a number to be processed:\n");
        scanf("%d",&request);
        
        if(write(fd2[1], &request, sizeof(request)) == -1){
            printf("Failed to write request in the buffer!\n");
            return -3;
        }

        printf("request sent...\n");
        sleep(2);

        int response;
        if(read(fd1[0], &response, sizeof(response)) == -1){
            printf("Failed to fetch response from the buffer!\n");
            return -4;
        }
        sleep(2);
        printf("Response fetched from child, sucessfully: %d \n",response);
    }
    
    return 0;
}