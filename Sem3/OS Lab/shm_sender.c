#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Generate a unique key
    key_t key = ftok("shmfile", 65);
	char buffer[100];
    // Create a shared memory segment with size 1024 bytes
    int shmid = shmget((key_t)1234, 1024, 0666 | IPC_CREAT);

    // Attach the shared memory segment to the process's address space
    char *str = (char *) shmat(shmid, NULL, 0);
    // Write a message to the shared memory
    printf("Writing to shared memory...\n");
	read(0, buffer, 100);
    strcpy(str, buffer);

    // Detach the shared memory segment
    shmdt(str);

    printf("Message written to shared memory.\n");
    return 0;
}
