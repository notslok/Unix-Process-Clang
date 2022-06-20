//Practicing how to handle multiple pipes
//here..parent process forks two child process, then parent process supplies the first child process with a value through a pipe;
//the first child process receives the value through the pipe, add a constant to it and supplies the updated value to the second
// child process through the another pipe where this second child process again adds a constant value and finally delivers the final ans to the
// parent process through 3rd pipe.
//!!! NOTE: for simplicity we are initializing all the file descriptors in the parent it self, so that it can be inherited by its child processes !!!

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
    int fd[3][2];//3 file descriptor variables
    for(int i=0;i<3;i++){
        if(pipe(fd[i]) == -1){
            return 1;
        }
    }
    int getval;
    printf("\nEnter a value to be processed:\n");
    scanf("%d",&getval);
    if(write(fd[0][1],&getval,sizeof(int)) == -1){
        return 99;
    }
    //----forking child 1
    int pid1 = fork();
    if(pid1 == -1){
        return 2;
    }
    if(pid1 == 0){
        close(fd[0][1]);
        close(fd[2][0]);
        close(fd[2][1]);
        close(fd[1][0]);
        int val1;
        if(read(fd[0][0],&val1,sizeof(int)) == -1){
            return 3;
        }
        val1+=10;
        if(write(fd[1][1],&val1,sizeof(int)) == -1){
            return 4;
        }
        close(fd[0][0]);
        close(fd[1][1]); 
        // printf("here");  
    }

    //------forking child 2
    int pid2 = fork();
    if(pid2 == -1){
        return 2;
    }
    if(pid2 == 0){
        // sleep(5);
        close(fd[0][1]);
        close(fd[0][0]);
        close(fd[1][1]);
        close(fd[2][0]);
        int val2;
        if(read(fd[1][0],&val2,sizeof(int)) == -1){
            return 3;
        }
        val2+=10;
        if(write(fd[2][1],&val2,sizeof(int)) == -1){
            return 4;
        }
        close(fd[2][1]);
        close(fd[1][0]);
    }

    if(read(fd[2][0],&getval,sizeof(int)) == -1){
        return 99;
    }
    close(fd[2][0]);
    close(fd[0][1]);
    close(fd[0][0]);
    close(fd[1][1]);
    close(fd[1][0]);
    close(fd[2][1]);

    waitpid(pid1,NULL,0);
    waitpid(pid1,NULL,0);

    printf("\nFinal value is: %d\n",getval);
    
    return 0;
}