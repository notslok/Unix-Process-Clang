//understanding the flow of execution of fork()
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>//only in unix based system...for fork()

int main(int argc, char* argv[]){   
//!!! fork returns "pid_t" type data

/*
                                    // execution line/instance tracing:
                                    //                                |             
                                    //                                |  
                                    //                                |
                                    //                                |
                                    //                                V
    fork();                         //---fork called---------------> | |  
    printf("hello forked world!\n");//2^(no. of fork())              | |
                                    //                               V V
*/
printf("\n----------------------------------------------------\n");
/*
    int id=fork();//for child process at a given level it returns 0, whereas for parent its  >0
    printf("Hello world from pid: %d\n",id);
    //output:
    // Hello world from pid: 15129 -> parent process
    // Hello world from pid: 0 -> child process
*/
printf("\n----------------------------------------------------\n");
/*
                                                        //trace:
                                                        //      P
                                                        //      |
    int id = fork();                                    //     P C
    if(id==0){                                          //     x C      
        printf("hello from child process!");            //       C   
    }                                                   //       C             
    else{                                               //     P 
        printf("hello from parent process!");           //     P 
    }                                                   //     P 
    //output:
    // hello from parent process!
    // hello from child process!
*/
printf("\n----------------------------------------------------\n");
/*
    //multiple continuous forks----2^n outputs
    fork();
    fork();
    fork();//here n=3;
    printf("hello world!\n");
    //output:(un predictable insertion of "\n" observed(?))
    // hello world!

    // hello world!
    // hello world!
    // hello world!
    // hello world!
    // hello world!
    // hello world!

    // hello world!
*/
printf("\n----------------------------------------------------\n");
/*
    //letting only 3 branches to form out of 2 consecutive forks...i like to call it slicing

    int id = fork();
    if(id!=0){
        fork();//can only be accessed by parent, so in total, only 3 processes. 
    }
    printf("hello world!\n");
*/
return 0;
}