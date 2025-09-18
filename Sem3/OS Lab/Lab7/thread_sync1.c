#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function that each thread will execute
void* printMessage(void* arg) {
    char* message = (char*)arg;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Messages to be printed by each thread
    char* message1 = "Hello from Thread 1!";
    char* message2 = "Hello from Thread 2!";

    // Create two threads
    if (pthread_create(&thread1, NULL, printMessage, message1) != 0) {
        perror("Failed to create Thread 1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, printMessage, message2) != 0) {
        perror("Failed to create Thread 2");
        return 1;
    }

    // Wait for both threads to finish
    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join Thread 1");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join Thread 2");
        return 1;
    }

    printf("Both threads have finished executing.\n");
    return 0;
}