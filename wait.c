/*
Printing numbers 1-10 in such a way that first 5 numbers are printed by 
child process whereas, the next 5 numbers are printed by parent process.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//----------------
#include<unistd.h> // fork()
#include<sys/wait.h> // wait()
int main(int argc, char* argv[]){
    int number;
    int id = fork();

    if(id==0){  //i.e. child process
        number=1;
    }else if(id>0){ //i.e. parent process
        number=6;
    }
    //first 5 numbers are to be printed by child process
    //so hold off the parent process till child process 
    //completes its execution.
    if(id!=0){
        //!!!Note: just wait(); willgive too few args error!!!
        wait(NULL);
        //just holds the current process until its child finishes.
        //!!! returns the finished child process id if child exists otherwise return -1.
    }
    for(int i=number;i<number+5;i++){
        printf("%d ",i);
        fflush(stdout);
        //doesnt let the output stored in stdout buffer, direstly flushes and prints it.
        
    }

    if(id!=0){
        printf("\n");//when finally parent finishes its execution, append a line-break.
    }
    return 0;
}