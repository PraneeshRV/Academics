#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) { 
	    perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        printf("Child process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(30); 
    }
    else { 
        printf("Parent process: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(40); 
        wait(NULL);
    }

    return 0;
}
