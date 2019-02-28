#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

int main(){
    pid_t pid;
    // printf("1. ----- PID: %d\n",pid);
    // fork a child process
    pid = fork();
    pid = fork();
    // printf("2. ----- PID: %d\n",pid);
    if (pid < 0){ // error occured
        fprintf(stderr,"Fork Failed");
        return 1;
    }

    else if (pid == 0){ // child process
        printf("Child exec\n");
        execlp("/bin/ls","ls",NULL);
    }
    else{ //parent process
        //parent will wait for the child to complete
        wait(NULL);
        printf("Child Complete\n");
    }

    return 0;

}