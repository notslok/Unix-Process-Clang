#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
#include<unistd.h>//fork()
#include<sys/wait.h>//wait()
#include<errno.h>// errno

int main(int argc, char* argv[]){
    int id1 = fork();
    int id2 = fork();
    if(id1 != 0){
        if(id2 != 0){
            printf("I am the main parent node!...I have created child process 'x' and 'y' through first and second fork calls respectively! :: %d\n",getpid());
        }
        else if(id2 == 0){
            printf("I am child process 'y' created by second fork!...and as last fork call id assigned me zero i am a leaf!!! :: %d\n",getpid());
        }   
    }
    else if(id1 == 0){
        if(id2 != 0){
            printf("I am child process 'x' created by main parent in first fork() call! :: %d\n",getpid());
        }else if(id2 == 0){
            // sleep(3);
            printf("I am process 'z'  created in second fork() call by process 'x' and as last fork() gave me pid=0 so i am a leaf! :: %d\n",getpid());
        }
    }

    //waiting for all the indirect child process to end before terminating parent process
    while(wait(NULL) != -1 || errno != ECHILD){
        printf("As a parent i am waiting all my direct and indirect child process to end...before i terminate! :: %d\n",getpid());
        fflush(stdout);
    }
    return 0;
}