//testing the scenario where parent process finishes first..i.e. when
//child process becomes zombie process
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
#include<unistd.h>//fork()
#include<sys/wait.h>//wait()

int main(int argc,char* argv[]){
    int id = fork();
    
    if(id==0){
        sleep(1);//delaying so that in the meantime parent process can finish first
    }

    printf("Current process' id:%d :: Parent process' id:%d\n",getpid(),getppid());
    //getpid()->return pid of current process
    //getppid()->returns pid of current process' parent process

    //!!! output:
    // Current process' id:24189 :: Parent process' id:24188
    // Current process' id:24190 :: Parent process' id:2346
    //!!! NOTE: !!!
    // here the zombie process: 24190 was assigned process 2346 as parent
    // which is systemd in my system's case it is the first daemon
    // to start while booting and last daemon to terminate during shutdown,
    // its pid = 1;

    int res=wait(NULL);
    if(res==-1){
        printf("Process with id of %d has no child process currently!\n",getpid());
    }else{
        printf("Child Process with id of %d executed successfully!\n",res);
    }
    return 0;
} 