#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

//

int main(int argc, char* argv[]){
    int arr[5];
    //open and read from named pipe------------
    int fd = open("fifo",O_RDONLY);
    if(fd == -1){
        printf("Error while opening the named pipe for reading!\n");
        return -2;
    }
    //
    if(read(fd,arr,sizeof(int)*5) == -1){
        printf("error reading file!\n");
        return -3;
    };
    close(fd);
    //-------perform addition and store result for sending to client side
    int ans=0;
    for(int i=0;i<sizeof(arr)/sizeof(int);i++){
        ans+=arr[i];
    }
    printf("Trans mitting the result to the client side...\n");

    //open named pipe in write mode for writing the server sideresponse
    int fd2 = open("fifo",O_WRONLY);
    if(fd2 == -1){
        printf("ERROR WHILE WRITING RESPONSE!\n");
        return -4;
    }
    sleep(5);
    if(write(fd2,&ans,sizeof(ans)) == -1){
        printf("Error while writing response!\n");
        return -5;
    };
    close(fd2);
    
    printf("Response sent successfully!\n");
    
    return 0;
}