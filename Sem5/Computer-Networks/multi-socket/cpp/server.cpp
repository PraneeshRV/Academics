#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

using namespace std;

string encrypt(string text, int shift) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            // Check if uppercase or lowercase
            int base = isupper(c) ? 'A' : 'a';
            // Shift the character
            char new_char = ((c - base + shift) % 26) + base;
            result += new_char;
        } else {
            result += c;
        }
    }
    return result;
}

string decrypt(string text, int shift) {
    return encrypt(text, -shift);
}

int main() {
    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cout << "Error creating socket" << endl;
        return -1;
    }

    // Server address setup
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cout << "Bind failed" << endl;
        return -1;
    }

    // Listen for connections
    if (listen(server_socket, 2) < 0) {
        cout << "Listen failed" << endl;
        return -1;
    }

    cout << "Server ready and waiting for clients..." << endl;

    // Accept first client
    struct sockaddr_in client1_addr;
    socklen_t client1_len = sizeof(client1_addr);
    int client1 = accept(server_socket, (struct sockaddr*)&client1_addr, &client1_len);
    cout << "Client 1 connected" << endl;

    // Get key from client 1
    send(client1, "Enter your key:", 15, 0);
    char buffer1[1024];
    recv(client1, buffer1, sizeof(buffer1), 0);
    int key1 = stoi(string(buffer1));
    cout << "Client 1 key: " << key1 << endl;

    // Accept second client
    struct sockaddr_in client2_addr;
    socklen_t client2_len = sizeof(client2_addr);
    int client2 = accept(server_socket, (struct sockaddr*)&client2_addr, &client2_len);
    cout << "Client 2 connected" << endl;

    // Get key from client 2
    send(client2, "Enter your key:", 15, 0);
    char buffer2[1024];
    recv(client2, buffer2, sizeof(buffer2), 0);
    int key2 = stoi(string(buffer2));
    cout << "Client 2 key: " << key2 << endl;

    cout << "Both clients connected! Chat can begin." << endl;

    // Main chat loop
    while (true) {
        // Handle message from client 1 to client 2
        memset(buffer1, 0, sizeof(buffer1));
        int bytes_received = recv(client1, buffer1, sizeof(buffer1), 0);
        
        if (bytes_received <= 0 || string(buffer1) == "Exit") {
            send(client2, "Exit", 4, 0);
            cout << "Chat ended by Client 1" << endl;
            break;
        }

        // Decrypt message from client 1
        string decrypted_message = decrypt(string(buffer1), key1);
        cout << "Client 1 says: " << decrypted_message << endl;

        // Encrypt for client 2 and send
        string encrypted_for_client2 = encrypt(decrypted_message, key2);
        send(client2, encrypted_for_client2.c_str(), encrypted_for_client2.length(), 0);

        // Handle message from client 2 to client 1
        memset(buffer2, 0, sizeof(buffer2));
        bytes_received = recv(client2, buffer2, sizeof(buffer2), 0);
        
        if (bytes_received <= 0 || string(buffer2) == "Exit") {
            send(client1, "Exit", 4, 0);
            cout << "Chat ended by Client 2" << endl;
            break;
        }

        // Decrypt message from client 2
        decrypted_message = decrypt(string(buffer2), key2);
        cout << "Client 2 says: " << decrypted_message << endl;

        // Encrypt for client 1 and send
        string encrypted_for_client1 = encrypt(decrypted_message, key1);
        send(client1, encrypted_for_client1.c_str(), encrypted_for_client1.length(), 0);
    }

    // Close connections
    close(client1);
    close(client2);
    close(server_socket);
    cout << "Server closed" << endl;

    return 0;
}
