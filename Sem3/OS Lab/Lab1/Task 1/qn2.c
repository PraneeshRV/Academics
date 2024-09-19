#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_BUFFER 1024

int main() {
    char message[] = "I'm home";
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {

        int fd_read, fd_write;
        char buffer[MAX_BUFFER];
        ssize_t bytes_read;

        fd_read = open("Code/secret.txt", O_RDONLY);
        if (fd_read == -1) {
            perror("Error opening source file");
            exit(1);
        }

        fd_write = open("secret_copied.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_write == -1) {
            perror("Error creating destination file");
            close(fd_read);
            exit(1);
        }


        while ((bytes_read = read(fd_read, buffer, MAX_BUFFER)) > 0) {
            if (write(fd_write, buffer, bytes_read) != bytes_read) {
                perror("Error writing to destination file");
                close(fd_read);
                close(fd_write);
                exit(1);
            }
        }

        close(fd_read);
        close(fd_write);

        exit(0);
    } else {

        int status;
        wait(&status);

        printf("%s\n", message);

        FILE *report = fopen("report.txt", "a");
        if (report == NULL) {
            perror("Error opening report.txt");
            return 1;
        }
        fprintf(report, "you are hacked\n");
        fclose(report);
    }

    return 0;
}
