#include <iostream>
#include <fstream>
#include <cstring>
#define MAX_USERS 5
#define MAX_ATTEMPTS 3
#define MAX_LEN 30
unsigned int simpleHash(const char* str) {
unsigned int hash = 0;
while (*str) {
hash = hash * 31 + *str;
str++;
}
return hash;
}
int main() {
char storedUsernames[MAX_USERS][MAX_LEN];
char storedPlaintext[MAX_USERS][MAX_LEN];
std::ifstream file("password_hash.txt");
if (!file) {
std::cerr << "Could not open password.txt\n";
return 1;
}
for (int i = 0; i < MAX_USERS; i++) {
file >> storedUsernames[i] >> storedPlaintext[i];
}
file.close();
char enteredUsername[MAX_LEN], enteredPassword[MAX_LEN];
int attemptCount = 0;
bool loginSuccess = false;
while (attemptCount < MAX_ATTEMPTS) {
std::cout << "Enter username: ";
std::cin.getline(enteredUsername, MAX_LEN);
std::cout << "Enter password: ";
std::cin.getline(enteredPassword, MAX_LEN);
unsigned int enteredHash = simpleHash(enteredPassword);
for (int i = 0; i < MAX_USERS; i++) {
if (strncmp(enteredUsername, storedUsernames[i], MAX_LEN) == 0 &&
enteredHash == simpleHash(storedPlaintext[i])) {
std::cout << "Authentication Successful \n";
loginSuccess = true;
break;
}
}
if (loginSuccess) break;
attemptCount++;
if (attemptCount < MAX_ATTEMPTS)
std::cout << "Authentication failed . Try again.\n";
else
std::cout << "Limit exceeded . Access denied.\n";
}
return 0;
}

