#include <stdio.h>
int main() {
    char message[] = "I'm home";
    pid_t pid;

    pid = fork();
printf("%s",message);
}
