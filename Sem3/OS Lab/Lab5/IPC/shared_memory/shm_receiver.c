#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    // Generate the same unique key as the writer
    key_t key = ftok("shmfile", 65);

    // Access the shared memory segment created by the writer
    int shmid = shmget((key_t)1234, 1024, 0666);

    // Attach the shared memory segment to the process's address space
    char *str = (char *) shmat(shmid, NULL, SHM_RDONLY);

    // Read the message from shared memory
    printf("Reading from shared memory...\n");
    printf("Data: %s\n", str);

    // Detach from the shared memory segment
    shmdt(str);

    // Destroy the shared memory segment
    shmctl(shmid, IPC_RMID, NULL);

    printf("Shared memory destroyed.\n");
    return 0;
}