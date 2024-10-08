#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <openssl/des.h>

#define SHM_SIZE 1024

void des_encrypt(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *ciphertext) {
    DES_cblock des_key;
    DES_key_schedule key_schedule;

    memcpy(des_key, key, 8);
    DES_set_key_unchecked(&des_key, &key_schedule);

    for (int i = 0; i < plaintext_len; i += 8) {
        DES_ecb_encrypt((DES_cblock *)(plaintext + i), (DES_cblock *)(ciphertext + i), &key_schedule, DES_ENCRYPT);
    }
}

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    char *shared_memory = (char *)shmat(shmid, NULL, 0);

    char input[SHM_SIZE];
    unsigned char ciphertext[SHM_SIZE];
    unsigned char des_key[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

    printf("Enter a message to encrypt and send: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline

    int input_len = strlen(input);
    int padded_len = ((input_len + 7) / 8) * 8; // Ensure length is multiple of 8

    des_encrypt((unsigned char *)input, padded_len, des_key, ciphertext);

    // Write key and ciphertext to shared memory
    memcpy(shared_memory, des_key, 8);
    memcpy(shared_memory + 8, &padded_len, sizeof(int));
    memcpy(shared_memory + 8 + sizeof(int), ciphertext, padded_len);

    printf("Encrypted message written to shared memory.\n");

    shmdt(shared_memory);
    return 0;
}