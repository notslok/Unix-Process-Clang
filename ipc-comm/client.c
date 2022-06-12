//communication b/w two processes for sum of 5 randomly generated numbers at client side
//***Build and run client and server files in parallel. 
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>//srand() and rand()

int main(int argc,char* argv[]){
    srand(time(NULL));
    int arr[5];
    for(int i =0;i<5;i++){
        sleep(2);
        arr[i]=rand()%10;
        printf("Generated %d\n",arr[i]);
    }

    //opeining writing in the named pipe------------------
    printf("Waiting for results from server side...\n");
    
    int fd = open("fifo",O_WRONLY);
    if(fd == -1){
        printf("Error while opening named pipe for writing!\n");
        return -2;
    }
    if(write(fd,arr,sizeof(arr)) == -1){
        printf("Error while writing the request!\n");
        return -3;
    };
    close(fd);

    //----receiving and reading the response from server side...    
    
    
    int fd2 = open("fifo",O_RDONLY);
    if(fd2 == -1){
        printf("Failed to open server side response!\n");
        return -4;
    }
    int response;
    if(read(fd,&response,sizeof(int)) == -1){
        printf("Failed to read server side response!\n");
        return -5;
    }
    close(fd2);

    printf("Response to the request fetched:\n");
    printf("%d\n",response);
    //
    return 0;
}