//Here we redirect the streams bound to be writting in STDOUT file descriptor and replace STDOUT with our file at STDOUT_FILENO
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>


int main(int argc, char* argv[]){
    int id = fork();
    if(id==-1){
        return 1;
    }

    if(id == 0){
        int myFile = open("ping.txt", O_WRONLY | O_CREAT, 0777); // O_CREAT -> create file if it doent exist already
        dup2(myFile, STDOUT_FILENO);//assigns stdout file discriptor to our file
        close(myFile);

        int err = execlp("ping","ping","-c","3","google.com",NULL);
        if(err == -1){
            return 2;
        }
    }
    else{
        int wait_status;
        wait(&wait_status);
        
        if(WIFEXITED(wait_status)){
            
            if(WEXITSTATUS(wait_status)){ // i.e error is != 0
                printf("Error thrown: %d\n",WEXITSTATUS(wait_status));
            }else{
                printf("SUCCESS IN LOGGING PING RESULTS!\n");
            }
        }
    }

    return 0;
}