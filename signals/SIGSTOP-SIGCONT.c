#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

int main(int argc, char* argv[]){
    int pid = fork();
    if(pid == -1){
        return 1;
    }
    if(pid == 0){
        while(1){
            printf("Printing something ...\n");
            usleep(50000);
        };
    }
    else{
        kill(pid,SIGSTOP);

        int timer_value=0;
        do{
            printf("Enter Timer Value:\n");
            scanf("%d",&timer_value);
            
            if(timer_value > 0){
                kill(pid,SIGCONT);
                sleep(timer_value);
                kill(pid,SIGSTOP);
            }
        
        }while(timer_value > 0);
        ///
        kill(pid,SIGKILL);
        
        //waiting for child process to end
        int wstatus;
        wait(&wstatus);

        if(WIFEXITED(wstatus)){ //if a non zero wait status code is returned
            if(WEXITSTATUS(wstatus)){
                printf("Program terminated prematurely!\n");
            }
        }
    }
    return 0;
}