//------------------------------------------------ simulating pipe "|" operator of unix terminal --------------------------------------------
// We will try to simulate following teminal command:
// ping -c 5 google.com | grep rtt
//-------------------------------------------------------------------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
    int fd[2];//[0]->read [1]->write
    if(pipe(fd) == -1){//couldn't open pipe
        return 2;
    }

    //------------------------ping child process:
    int pid_ping = fork();
    if(pid_ping == -1){// couldn't fork child process
        return 3;
    }
    
    //!!! NOTE: the child process will be replaced with "ping" executable program...  
    
    if(pid_ping == 0){//child process (1) -> to be replaced with "ping"
        
        dup2(fd[1],STDOUT_FILENO);//"duplicating and then replacing" the stdout file descriptor of the child process with write end of our file descriptor fd
        //closing this child's copy of file descriptor
        close(fd[0]);//closing the read end of the file
        close(fd[1]);//closing the write end of the file as we have already duplicated it

        execlp("ping","ping","-c","5","google.com",NULL);// l->argument list    p->using path variables
        //this now writes the output in our stdout file descriptor which we have replaced with our custom file descriptors write end
        //so the output is going to be dumped in our file descriptor's write end.
    }

    //-------------------grep child process:
    int pid_grep = fork();
    if(pid_grep == -1){
        return 4;
    }

    //!!! NOTE: the child process will be replaced with "grep" executable program...
    
    if(pid_grep == 0){//child process to handle "grep"
        dup2(fd[0],STDIN_FILENO);//"duplicating and replacing" read end of custom file descriptor, so that the stdin file descriptor points to our custom file descriptor's read end
        //closing this child's file descriptors 
        close(fd[1]);
        close(fd[0]);
        //exec lp below will now be taking input from the read end of our custom pipe
        execlp("grep","grep","rtt",NULL);//search for the keywork "rtt" in input(read end of custom file descriptor)
    }

    //closing the main parent process' copy of file descriptor otherwise grep will keep waiting for an input
    close(fd[0]);
    close(fd[1]);

    //waiting for both child processes to complete
    waitpid(pid_ping,NULL,0);
    waitpid(pid_grep,NULL,0);
    return 0;
}