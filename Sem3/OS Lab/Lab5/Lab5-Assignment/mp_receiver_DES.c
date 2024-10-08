#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <openssl/des.h>

#define PIPE_NAME "/tmp/des_pipe"
#define MAX_BUF 1024

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
    int fd;
    unsigned char des_key[8];
    int ciphertext_len;
    unsigned char ciphertext[MAX_BUF];
    char plaintext[MAX_BUF];

    // Open pipe for reading
    fd = open(PIPE_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Read key, ciphertext length, and ciphertext from pipe
    read(fd, des_key, 8);
    read(fd, &ciphertext_len, sizeof(int));
    read(fd, ciphertext, ciphertext_len);

    close(fd);

    des_decrypt(ciphertext, ciphertext_len, des_key, (unsigned char *)plaintext);
    plaintext[ciphertext_len] = '\0';

    printf("Decrypted message: %s\n", plaintext);

    // Remove the named pipe
    unlink(PIPE_NAME);

    return 0;
}