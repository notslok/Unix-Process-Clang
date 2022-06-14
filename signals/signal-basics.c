#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
#include<signal.h>//kill()

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){
        return 1;
    } 
    if(pid == 0){
        while(1){
            usleep(100000);//takes in microseconds
            printf("In child process!\n");
        }
    }else{
        sleep(4);
        kill(pid,SIGKILL);//this is the pid of child as during forking when memory is copied the parent is returned child process pid val, while child gets 0 returned
        
        int wstatus;
        wait(&wstatus);

        if(WIFEXITED(wstatus)){// if child terminated abruptly
            if(WEXITSTATUS(wstatus)){ // if terminated with non zero exit status
                printf("Error thrown with exit code : %d\n",WEXITSTATUS(wstatus));
            }
        }

    }
    return 0;
}