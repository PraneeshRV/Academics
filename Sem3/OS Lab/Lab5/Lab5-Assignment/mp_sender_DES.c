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
    int fd;
    char input[MAX_BUF];
    unsigned char ciphertext[MAX_BUF];
    unsigned char des_key[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

    // Create named pipe if it doesn't exist
    mkfifo(PIPE_NAME, 0666);

    printf("Enter a message to encrypt and send: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline

    int input_len = strlen(input);
    int padded_len = ((input_len + 7) / 8) * 8; // Ensure length is multiple of 8

    des_encrypt((unsigned char *)input, padded_len, des_key, ciphertext);

    // Open pipe for writing
    fd = open(PIPE_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Write key, ciphertext length, and ciphertext to pipe
    write(fd, des_key, 8);
    write(fd, &padded_len, sizeof(int));
    write(fd, ciphertext, padded_len);

    close(fd);
    printf("Encrypted message sent through pipe.\n");

    return 0;
}