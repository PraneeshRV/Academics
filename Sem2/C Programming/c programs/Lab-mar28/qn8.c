#include <stdio.h>
#include <String.h>

void reverseString(char *str)
{
    char *start_ptr = str;
    char *end_ptr = str;

    while (*end_ptr != '\0')
    {
        end_ptr++;
    }

    end_ptr--;

    while (end_ptr >= start_ptr)
    {
        printf("%c ", *end_ptr);
        end_ptr--;
    }
}

int main()
{
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin); 
    str[strlen(str) - 1] = '\0';

    printf("The string in reverse order is: ");
    reverseString(str);

    return 0;
}
