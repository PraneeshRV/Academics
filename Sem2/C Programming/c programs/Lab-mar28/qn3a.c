#include <stdio.h>

int stringLength(char *str)
{
    char *ptr = str;
    int length = 0;

    while (*ptr != '\0')
    {
        length++;
        ptr++;
    }

    return length;
}

int main()
{
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    
    str[stringLength(str) - 1] = '\0';

    printf("The length of the string is: %d\n", stringLength(str));
    return 0;
}
