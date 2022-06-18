//ask for a random multiplication answer...then wait for 5 secs if ans not given give a hint
//and wait for answera and print the required verdict 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
#include<signal.h>//kill()
//
int ans=-1;
void handle_SIGUSR1(int sig){
    if(ans == -1)
        printf("\n(HINT) Multiplication is just repetitive adition...\n");
}
//
int main(int argc, char* argv[]){
    //random variables are placed here so that they can be copied/inherited by both child and parent processes
    srand(time(NULL));
    int num1 = rand()%10+1;
    int num2 = rand()%10+1;
    
    //forking
    int pid = fork();
    if(pid == -1){
        return 1;
    }
    
    if(pid==0){//child process
        sleep(5);//wait for 5 secs in child and then throw SIGUSR1 signal on the parents pid (getppid())
        kill(getppid(),SIGUSR1);//SIGUSR1 & SIGUSR2 are set aside for user's custom usage
    }
    else{//parent process
        
        //signal handling
        struct sigaction sa;
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_SIGUSR1;
        sigaction(SIGUSR1,&sa,NULL);//bind the sa sigaction struct with SIGUSR1 signal

        printf("What does %d * %d equals to?\n",num1,num2);
        scanf("%d",&ans);
        if(ans == num1*num2){
            printf("Right Answer!!!\n");
        }else{
            printf("Wrong Answer!!!\n");
        }
    }
    wait(NULL);//wait for child process to finish...a safeguard agaist resulting in zombie process and hence memory leak
    return 0;
}