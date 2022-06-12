#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
#include<unistd.h>//fork(), pipe()
#include<sys/wait.h>//wait()
#include<errno.h>// eerno

int main(int argc,char* argv[]){
    int file_descriptor[2];//after fork() it is both copied and inherited by child process
    //file_descriptor[0]->read
    //file_descriptor[1]->write
    if(pipe(file_descriptor) == -1){
        printf("Error while opening the pipe!\n");
        return -99;
    }
    //--------------------------
    int id=fork();
    //------------------------
    if(id==0){
        close(file_descriptor[0]);//closing read end as we dont require it in child process
        char message[2];// entering more than two char will lead in "stack smashing error"-> signifies buffer overflow
        printf("Enter the message you want to relay to parent process:\n");
        scanf("%s",message);
        
        if(write(file_descriptor[1],message,sizeof(message)) == -1){
            printf("Error while writing in the file descriptor buffer!\n");
            return -3;
        };
        close(file_descriptor[1]);
    }
    else{
        close(file_descriptor[1]);//closing the writing end of pipe as it is not required in the parent process
        char child_message[2];
        
        if(read(file_descriptor[0],child_message,sizeof(child_message)) == -1){
            printf("Error while reading from the file descriptor buffer!\n");
            return -4;
        };
        printf("Child proces says: %s \n",child_message);
        close(file_descriptor[0]);
    }
    return 0;
}