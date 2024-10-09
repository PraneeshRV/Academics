#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define MAX 100

struct message_buffer {
    long message_type;
    char message_text[MAX];
};

#include <string.h>

void XOR_encrypt_decrypt(char *input, char *key, char *output) {
    int i, key_len = strlen(key);
    for (i = 0; input[i] != '\0'; i++) {
        output[i] = input[i] ^ key[i % key_len];  
    }
    output[i] = '\0'; 
}
int main() {
    key_t key;
    int msgid;
    struct message_buffer message;
    char decrypted[MAX];
    char *XOR_key = "mysecretkey"; 
    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgid, &message, sizeof(message), 1, 0);

    XOR_encrypt_decrypt(message.message_text, XOR_key, decrypted);

    printf("Decrypted message: %s\n", decrypted);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}


