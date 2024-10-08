#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

void XOR_encrypt_decrypt(char *input, char *key, char *output) {
    int i, key_len = strlen(key);
    for (i = 0; input[i] != '\0'; i++) {
        output[i] = input[i] ^ key[i % key_len]; 
    }
    output[i] = '\0'; 
}

int main() {
    key_t key = ftok("shmfile", 65);
    char buffer[100], encrypted[100];
    char *XOR_key = "mysecretkey";  
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    char *str = (char *) shmat(shmid, NULL, 0);

    if (str == (char *)-1) {
        perror("shmat failed");
        return 1;
    }

    printf("Enter a message to encrypt: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        perror("fgets failed");
        return 1;
    }

    // Remove newline character if present
    buffer[strcspn(buffer, "\n")] = '\0';

    XOR_encrypt_decrypt(buffer, XOR_key, encrypted);
    strcpy(str, encrypted);

    if (shmdt(str) == -1) {
        perror("shmdt failed");
        return 1;
    }

    printf("Encrypted message written to shared memory.\n");
    return 0;
}


