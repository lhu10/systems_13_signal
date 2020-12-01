#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

static void int_handler(int signo){
    if(signo == SIGINT){
        int fd, result; 
        char msg[] = "Program Exited due to SIGINT";
        fd = open("output.txt", O_APPEND | O_WRONLY | O_CREAT, 0644);
        if(fd == -1){
            printf("Error %d: %s\n", errno, strerror(errno));
            return -1;
        }
        result = write(fd, msg, sizeof(msg)-1);
        if(result == -1){
            printf("Error %d: %s\n", errno, strerror(errno));
            return -1; 
        }
        close(fd);
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
