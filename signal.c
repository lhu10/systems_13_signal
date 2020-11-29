#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void int_handler(int signo){
    if(signo == SIGINT){
        printf("Program Exited due to SIGINT\n");
        exit(0);
    }
}

static void usr1_handler(int signo){
    if(signo == SIGUSR1){
        printf("PID of Parent: %d\n", getppid());
    }
}

int main(){

    signal(SIGINT, int_handler);
    signal(SIGUSR1, usr1_handler);
    kill(getpid(), SIGUSR1);
    
    while(1){
        printf("PID of process: %d\n", getpid());
        sleep(1);
    }

    return 0; 
}
