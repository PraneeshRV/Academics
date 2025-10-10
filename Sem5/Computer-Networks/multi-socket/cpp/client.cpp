#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
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

void receive_messages(int client_socket, int my_key) {
    char buffer[1024];
    
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        
        if (bytes_received <= 0 || string(buffer) == "Exit") {
            cout << "\nChat ended by other user." << endl;
            break;
        }
        
        // Decrypt the message
        string decrypted_message = decrypt(string(buffer), my_key);
        cout << "\nFriend: " << decrypted_message << endl;
        cout << "You: ";
        cout.flush();
    }
}

int main() {
    // Create client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        cout << "Error creating socket" << endl;
        return -1;
    }

    // Server address setup
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cout << "Connection failed" << endl;
        return -1;
    }

    // Get key prompt from server
    char buffer[1024];
    recv(client_socket, buffer, sizeof(buffer), 0);
    cout << buffer;  // "Enter your key:"

    // Enter our encryption key
    int my_key;
    cin >> my_key;
    
    // Send key to server
    string key_str = to_string(my_key);
    send(client_socket, key_str.c_str(), key_str.length(), 0);

    cout << "Connected to server!" << endl;
    cout << "Type 'Exit' to quit the chat." << endl << endl;

    // Start background thread to receive messages
    thread receive_thread(receive_messages, client_socket, my_key);
    receive_thread.detach();  // Thread will run independently

    // Main loop to send messages
    string message;
    cout << "You: ";
    
    while (true) {
        getline(cin, message);
        
        // Skip empty lines
        if (message.empty()) {
            cout << "You: ";
            continue;
        }
        
        // Encrypt and send message
        string encrypted_message = encrypt(message, my_key);
        send(client_socket, encrypted_message.c_str(), encrypted_message.length(), 0);
        
        // Exit if user types Exit
        if (message == "Exit") {
            break;
        }
        
        cout << "You: ";
    }

    // Close connection
    close(client_socket);
    cout << "Disconnected from server" << endl;

    return 0;
}
