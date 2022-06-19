//!!!! debug--->done

// 2 processes
// 1) child process should generate random numbers and send them to parent
// 2) Parent is going to sum all the numbers and print the result
//-----------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
//-----------------------------------------------------------------
int main(int argc, char* argv[]){
    int fd[2];//[0]->read [1]->write
    if(pipe(fd)==-1){
        return -99;
    }

    int pid = fork();
    
    if(pid == -1){
        return 98;
    }
    
    if(pid == 0){
        close(fd[0]);
        
        srand(time(NULL));

        int size = rand()%10+1;//a random assignment between 1-10
        int arr[size];
        for(int i=0;i<size;i++){
            arr[i]=rand()%10;
        }

        printf("Size of input array: %d\n",size);
        printf("Array sent to the parent process:\n");
        for(int i=0;i<size;i++){
            printf("%d ",arr[i]);
        }
        printf("\n");

        if(write(fd[1],&size,sizeof(int)) == -1){
            return 99;
        }
        if(write(fd[1],arr,sizeof(int)*size) == -1){
            return 99;
        }
        close(fd[1]);
    }
    else{
        close(fd[1]);
        // int arr[10];
        int* arr;
        int size;
        if(read(fd[0],&size,sizeof(int)) == -1){
            return 99;
        }
        
        arr=(int*)malloc(size*sizeof(int));

        if(read(fd[0],arr,sizeof(int)*size) == -1){
            return 99;
        }
        int sum=0;
        for(int i=0;i<size;i++){
            sum+=arr[i];
        }
        // printf("\nhere\n");
        
        close(fd[0]);
        printf("\n%d\n",sum);
        
        wait(NULL);
    }
    return 0;
}