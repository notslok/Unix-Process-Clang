//use another process like "$ cat mkfifio_1" to read the output and complete the execution!!!
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//
#include<unistd.h>// fork() and pipe()
#include<sys/wait.h>//wait()
#include<errno.h> // errno
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>//mkfifo()
//------------------------------------

int main(int argc, char* argv[]){
    //-----create named pipe "fifo" 
    
    if(mkfifo("mkfifo_1",0777) == -1){ //0777->gives permission to any user, to read-write-execute the created file.
        if(errno != EEXIST){//if file doent exist already and there was no error in mkfifo() then file error due to some other reason
            printf("Error in creating file!\n");
            return 1;
        }
    }
    
    //-----open the file and catch the returned file descriptor on opening the fifo
    
    int fd=open("mkfifo_1",O_RDWR);//opened in WRiteONLY mode, and variable fd caght the file descriptor returned 
    int num=98;
    if(write(fd,&num,sizeof(int)) == -1){
        printf("Write operation failed!\n");
        return 2;
    };
    close(fd);
    return 0;
}