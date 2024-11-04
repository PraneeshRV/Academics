#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define MAX 100

// Message structure
struct message_buffer {
    long message_type;
    char message_text[MAX];
};

int main() {
    key_t key;
    int msgid;
    struct message_buffer message;

    // Generate a unique key
    key = ftok("progfile", 65);

    // Access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive the message
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    // Display the message
    printf("Received message: %s\n", message.message_text);

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
