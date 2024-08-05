#include <stdio.h>

int compareStrings(char *str1, char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int main()
{
    char str1[100], str2[100];

    printf("Enter the first string: ");
    fgets(str1, sizeof(str1), stdin);

    printf("Enter the second string: ");
    fgets(str2, sizeof(str2), stdin);

    int result = compareStrings(str1, str2);

    if (result < 0)
    {
        printf("'%s' is less than '%s'.\n", str1, str2);
    }
    else if (result > 0)
    {
        printf("'%s' is greater than '%s'.\n", str1, str2);
    }
    else
    {
        printf("'%s' is equal to '%s'.\n", str1, str2);
    }

    return 0;
}
