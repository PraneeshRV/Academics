#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define MAX 100

struct message_buffer {
    long message_type;
    char message_text[MAX];
};

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
    char encrypted[MAX];
    char *XOR_key = "mysecretkey"; 
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.message_type = 1;

    printf("Enter a message to encrypt and send: ");
    scanf("%s", message.message_text);

    XOR_encrypt_decrypt(message.message_text, XOR_key, encrypted);
    strcpy(message.message_text, encrypted);

    msgsnd(msgid, &message, sizeof(message), 0);

    printf("Encrypted message sent: %s\n", encrypted);

    return 0;
}

