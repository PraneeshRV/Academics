#include <stdio.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_ATTEMPTS 3
#define USERNAME_LEN 32
#define PASSWORD_LEN 32

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} User;

int main() {
    User users[MAX_USERS];
    FILE *fp = fopen("password.txt", "r");
    if (!fp) { printf("Could not open password.txt\n"); return 1; }
    int count = 0;
    while (count < MAX_USERS && fscanf(fp, "%31s %31s", users[count].username, users[count].password) == 2) count++;
    fclose(fp);
    char input_username[USERNAME_LEN];
    char input_password[PASSWORD_LEN];
    int attempts = 0, authenticated = 0;
    while (attempts < MAX_ATTEMPTS && !authenticated) {
        printf("Enter username: ");
        if (scanf("%31s", input_username) != 1) break;
        printf("Enter password: ");
        if (scanf("%31s", input_password) != 1) break;
        for (int i = 0; i < count; i++) {
            if (strcmp(users[i].username, input_username) == 0 && strcmp(users[i].password, input_password) == 0) {
                authenticated = 1;
                break;
            }
        }
        if (authenticated) {
            printf("Authentication Successful\n");
        } else {
            attempts++;
            if (attempts < MAX_ATTEMPTS) printf("Authentication failed, try again\n");
        }
    }
    if (!authenticated) printf("Limit exceeded.\n");
    return 0;
}
