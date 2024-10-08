#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

void XOR_encrypt_decrypt(char *input, char *key, char *output) {
    int i, key_len = strlen(key);
    for (i = 0; input[i] != '\0'; i++) {
        output[i] = input[i] ^ key[i % key_len]; 
    }
    output[i] = '\0';  
    }

int main() {
    key_t key = ftok("shmfile", 65);
    char decrypted[100];
    char *XOR_key = "mysecretkey";  
    int shmid = shmget((key_t)1234, 1024, 0666);
    char *str = (char *) shmat(shmid, NULL, SHM_RDONLY);
    XOR_encrypt_decrypt(str, XOR_key, decrypted);
    printf("Decrypted message: %s\n", decrypted);
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Shared memory destroyed.\n");
    return 0;
}

