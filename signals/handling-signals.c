//handling foreground-background process signals
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>

void handle_SIGTSTP(int sig){
    printf("Process can't be stopped, SIGTSTP call ignored!!!\n");
    fflush(stdout);
    printf("Enter a desired number:\n");
    fflush(stdout);
}
//to check the SIGCONT signal handler comment out all the SIGTSTP signal handler assignment in the main. 
void handle_SIGCONT(int sig){
    printf("Responding to SIGCONT signal fired by 'fg' command...\n");
    printf("Enter a desired number:\n");
    fflush(stdout);
}

int main(int argc,char* argv[]){
    
    //----------Signal handling
    struct sigaction sa_stp;
    struct sigaction sa_cont;
    
    //id .sa_flags is set then the signals dont end by terminating on pressing ENTER
    // in the cases of SIGTSTP and SIGCONT
    sa_stp.sa_flags = SA_RESTART;
    sa_cont.sa_flags = SA_RESTART;
    
    //assigning new handlers to bothe SIGTSTP and SIGCONT signals
    sa_stp.sa_handler = &handle_SIGTSTP;
    sa_cont.sa_handler = &handle_SIGCONT;
    
    //binding the new handlers with their respective target signals
    sigaction(SIGTSTP,&sa_stp,NULL);
    sigaction(SIGCONT,&sa_cont,NULL);

    //------------------------ famous but faulty alternative, behaves differently on different distro not reccommended by man page 
    //  signal(SIGTSTP,&handle_SIGTSTP);
    
    int inp;
    printf("Enter a desired number:\n");
    
    scanf("%d",&inp);
    printf("%d times 5 = %d\n",inp,inp*5);
    return 0;
}