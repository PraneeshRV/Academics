#include <stdio.h>

int main()
{
    char ch, *ptr;

    for (ch = 'A'; ch <= 'Z'; ++ch)
    {
        ptr = &ch;
        printf("%c ", *ptr);
    }

    return 0;
}
