#define _GNU_SOURCE //...for execvpe() implicit declaration error...
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//for exec(), execlp(),execlpe(), execv(), execvpe() etc...
#include<errno.h>
#include<sys/wait.h>

int main( int argc, char* argv[]){
    int id=fork();
    if(id==-1){
        return 1;
    }
    //------------------------------
    if(id == 0){
        execlp(
            "ping",
            "ping",
            "-c",   //supplying argument "count" for ping command 
            "5",    //value for the argument "-c" of ping command
            "google.com",
            NULL
        );

        printf("If you can see this message then an error occured while  executing exec(), fetching error details...\n");
        sleep(3);
        int err_code=errno;
        printf("Returned with error code: %d\n",err_code);
        return 2;
    }
    else{//parent...so it should wait for child before begining its execution
        //error handling using wait status codes
        int wait_status;
        wait(&wait_status);

        if(WIFEXITED(wait_status)){//if this !=0 means the child process was not terminatted abruptly due to external factors
            int exit_status_code=WEXITSTATUS(wait_status);//fetching the status code returned
            if(exit_status_code == 0){ //this means the ping executable passed to execlp() is valid and it executed without error
                printf("\nChild process successfully executed given exec() fn!\n");
                printf("\npost processing goes here....\n");
            }else{//ping threw an error thats why exit status code !=0
                printf("Executable terminated with error code: %d\n",exit_status_code);
            }
        }
    }
    return 0; // return 0 for main follows the same logic as WEXITSTATUS()
}