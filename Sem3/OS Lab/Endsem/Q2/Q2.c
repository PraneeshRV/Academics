
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }
    else if (pid == 0) {
        if (num % 2 != 0) { 
            int fd = open("q2_a.txt", O_WRONLY | O_CREAT, 0644);
	    
            if (fd < 0) {
                printf("File creation failed\n");
                exit(1);
            }
            
            long long fact = 1;
            for(int i = 1; i <= num; i++) {
                fact *= i;
            }
            
            char buffer[100];
            sprintf(buffer, "%lld", fact);
            write(fd, buffer, strlen(buffer));
            close(fd);
            exit(0);
        }
        else {
            printf("Prime numbers from 0 to %d are:\n", num);
            for(int i = 2; i <= num; i++) {
                int isPrime = 1;
                for(int j = 2; j * j <= i; j++) {
                    if(i % j == 0) {
                        isPrime = 0;
                        break;
                    }
                }
                if(isPrime)
                    printf("%d ", i);
            }
            printf("\n");
            exit(0);
        }
    }
    else {
        wait(NULL);
        printf("Adios\n");
    }
    
    return 0;

}

