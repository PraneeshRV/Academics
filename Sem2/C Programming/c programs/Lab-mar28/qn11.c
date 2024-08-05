#include <stdio.h>
#include <string.h>

void extractSubstring(char *str, int start, int length, char *result)
{
    strncpy(result, &str[start], length);
    result[length] = '\0';
}

int main()
{
    char str[100], result[100];
    int start, length;

    printf("Enter the string: ");
    fgets(str, sizeof(str), stdin); 

    str[strlen(str) - 1] = '\0';

    printf("Enter the start location: ");
    scanf("%d", &start);

    printf("Enter the length: ");
    scanf("%d", &length);

    extractSubstring(str, start, length, result);

    printf("The extracted substring is: %s\n", result);

    return 0;
}
