/*

Adding numbers 1-10 using pipes

!!! NOTE: 
Compile manually->
$ gcc ipc.c
$ ./a.out

*/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//
#include<unistd.h>//fork() & pipe()
#include<sys/wait.h>//wait()
#include<errno.h>
//-----------------------------
//!!! NOTE: as per observation it seems...functions are also copied into child processess.        
int return_sum(int *arr,int start_idx,int end_idx){
    int sum=0;
    for(int i = start_idx;i < end_idx;i++){
        sum+=*(arr+i);
    }
    return sum;
}

int main(int argc, char* argv[]){
    int fd[2];
    //fd[0]->read
    //fd[1]->write
    int arr[10]={1,2,3,4,5,6,7,8,9,10};
    int pivot;
    scanf("%d",&pivot);
    if(pipe(fd) == -1){
        printf("Failed to create pipe!\n");
        return -2;
    }
    //
    int id = fork();
    if(id == -1){
        printf("Failed to spawn child process!\n");
        return -3;
    }
    //
    if(id == 0){
        close(fd[0]);
        int child_sum=return_sum(arr,0,pivot); //!!! NOTE: as per observation it seems...functions are also copied into child processess.
        
        if(write(fd[1],&child_sum,sizeof(int)) == -1){
            printf("Error while writting into the buffer!\n");
            return -4;
        };
        close(fd[1]);       
    }
    else{
        close(fd[1]);
        int child_sum;
        if(read(fd[0],&child_sum,sizeof(int)) == -1){
            printf("Error while reading from the buffer!\n");
            return -5;
        }
        int total_sum = child_sum + return_sum(arr,pivot,sizeof(arr)/sizeof(int));
        printf("The required sum is : %d\n",total_sum);
        close(fd[0]);
    }
    return 0;
}