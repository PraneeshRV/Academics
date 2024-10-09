#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared = 0; // Global shared variable

// Function for the increment thread
void* increment(void* arg) {
    
     int x;
        x=shared;
        x++;
        shared=x;
        printf("Thread1 reads the value of shared variable as %d\n",x);
        printf("Local updation by Thread1: %d\n",x);
        printf("Value of shared variable updated by Thread1 is: %d\n",shared);
    return NULL;
}

// Function for the decrement thread
void* decrement(void* arg) {
        int y;
        y=shared;
        printf("Thread2 reads the value as %d\n",y);
        y--;
        printf("Local updation by Thread2: %d\n",y);
        shared=y;
        printf("Value of shared variable updated by Thread2 is: %d\n",shared);
    return NULL;
}

int main() {
    pthread_t inc_thread, dec_thread;

    // Create the increment thread
    if (pthread_create(&inc_thread, NULL, increment, NULL) != 0) {
        perror("Failed to create increment thread");
        return 1;
    }

    // Create the decrement thread
    if (pthread_create(&dec_thread, NULL, decrement, NULL) != 0) {
        perror("Failed to create decrement thread");
        return 1;
    }

    // Wait for both threads to finish
    if (pthread_join(inc_thread, NULL) != 0) {
        perror("Failed to join increment thread");
        return 1;
    }

    if (pthread_join(dec_thread, NULL) != 0) {
        perror("Failed to join decrement thread");
        return 1;
    }

    // Output the final value of the shared variable
    printf("Final value of shared_var: %d\n", shared);
    return 0;
}