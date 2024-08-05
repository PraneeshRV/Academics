#include <stdio.h>
void main()
{
    char *ptr;
    char mystring[] = "abcdefg";
    ptr = mystring;
    ptr += 5;
    printf("%c", *ptr);
}