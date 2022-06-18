//toggling foreground-background process
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>

int main(int argc,char* argv[]){
    int inp;
    printf("Enter a desired number:\n");
    //if we press Ctrl+z right after this line then the terminal sends a SIGTSTP() signal to this main process and it becomes a background process.
    // to make it a foreground process again we simply type the comand "fg <pid>" to restore it, in this case to restore this instance of program
    // no pid is needed simply fg is enough. "fg" fires a SIGCONT signal internally to resume the process execution.

    //!!! NOTE:
/*

    >> Both signals (SIGSTOP & SIGTSTP) are designed to suspend a process which will be eventually resumed with SIGCONT. The main differences between them are:
    |
    *---> SIGSTOP is a signal sent programmatically (eg: kill -STOP pid ) while 
    |     SIGTSTP (for signal - terminal stop) may also be sent through the "tty" 
    |     driver by a user typing on a keyboard, usually Control-Z.
    |
    *---> SIGSTOP cannot be ignored. SIGTSTP might be.

*/
    scanf("%d",&inp);
    printf("%d times 5 = %d\n",inp,inp*5);
    return 0;
}