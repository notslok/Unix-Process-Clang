//A generalized version of multiple-pipes.c

//i.e. N number of process n number of pies n EVERYTHING!!!

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>

int main(int argc, char* argv[]){
    srand(time(NULL));
    int file_descriptor_size=rand()%10+1;//1 to 10
    printf("\nRounds generated: %d\n",file_descriptor_size);
    int fd[file_descriptor_size][2];//3 file descriptor variables
    
    for(int i=0;i<file_descriptor_size;i++){
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
    
    for(int i=0;i<file_descriptor_size-1;i++){
            int pid1 = fork();
            if(pid1 == -1){
                return 2;
            }
            if(pid1 == 0){
                int val1;
                if(read(fd[i][0],&val1,sizeof(int)) == -1){
                    return 3;
                }
                val1+=10;
                if(write(fd[i+1][1],&val1,sizeof(int)) == -1){
                    return 4;
                }
                // close(fd[0][1]);
                // close(fd[2][0]);
                // close(fd[2][1]);
                // close(fd[1][0]);
                // close(fd[0][0]);
                // close(fd[1][1]);  
                for(int i=0;i<file_descriptor_size;i++){
                    for(int j=0;j<=1;j++){
                        close(fd[i][j]);
                    }
                } 
            }
    }

    // //------forking child 2
    // int pid2 = fork();
    // if(pid2 == -1){
    //     return 2;
    // }
    // if(pid2 == 0){
    //     close(fd[0][1]);
    //     close(fd[0][0]);
    //     close(fd[1][1]);
    //     close(fd[2][0]);
    //     int val2;
    //     if(read(fd[1][0],&val2,sizeof(int)) == -1){
    //         return 3;
    //     }
    //     val2+=10;
    //     if(write(fd[2][1],&val2,sizeof(int)) == -1){
    //         return 4;
    //     }
    //     close(fd[2][1]);
    //     close(fd[1][0]);
    // }

    if(read(fd[file_descriptor_size-1][0],&getval,sizeof(int)) == -1){
        return 99;
    }
    for(int i=0;i<file_descriptor_size;i++){
                    for(int j=0;j<=1;j++){
                        close(fd[i][j]);
                    }
                } 

    // waitpid(pid1,NULL,0);
    // waitpid(pid1,NULL,0);

    printf("\nFinal value is: %d\n",getval);
    
    return 0;
}