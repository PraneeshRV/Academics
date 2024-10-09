#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <openssl/des.h>

#define SHM_SIZE 1024

void des_decrypt(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *plaintext) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;

    memcpy(des_key, key, 8);
    DES_set_key_unchecked(&des_key, &key_schedule);

    for (int i = 0; i < ciphertext_len; i += 8) {
        DES_ecb_encrypt((DES_cblock *)(ciphertext + i), (DES_cblock *)(plaintext + i), &key_schedule, DES_DECRYPT);
    }
}

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666);
    char *shared_memory = (char *)shmat(shmid, NULL, 0);

    unsigned char des_key[8];
    int ciphertext_len;
    unsigned char ciphertext[SHM_SIZE];
    char plaintext[SHM_SIZE];

    // Read key, ciphertext length, and ciphertext from shared memory
    memcpy(des_key, shared_memory, 8);
    memcpy(&ciphertext_len, shared_memory + 8, sizeof(int));
    memcpy(ciphertext, shared_memory + 8 + sizeof(int), ciphertext_len);

    des_decrypt(ciphertext, ciphertext_len, des_key, (unsigned char *)plaintext);
    plaintext[ciphertext_len] = '\0';

    printf("Decrypted message: %s\n", plaintext);

    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}