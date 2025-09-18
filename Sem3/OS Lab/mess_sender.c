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

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.message_type = 1;

    // Get the message from user
    printf("Enter a message to send: ");
    scanf("%s", message.message_text);

    // Send the message
    msgsnd(msgid, &message, sizeof(message), 0);
    
    printf("Message sent: %s\n", message.message_text);
    
    return 0;
}
