#include <stdio.h>
 int main()
{
    int a = 10;
    int *p = &a;
    int *ptr = p;
    printf("%u", *ptr);
    return 0;
}