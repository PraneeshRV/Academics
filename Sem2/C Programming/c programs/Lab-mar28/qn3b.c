#include <stdio.h>

int main()
{
    char str[100];
    char *ptr;
    int length = 0;

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    ptr = str;
    while (*ptr != '\0')
    {
        length++;
        ptr++;
    }

    length = length - 1;

    printf("The length of the string is: %d\n", length);

    return 0;
}
