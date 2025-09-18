#include <stdio.h>
void main()
{
    int a[] = {7, 2, 3, 4, 5}, *p;
    p = a;
    ++*p;
    printf("%d ", *p);
    p += 2;
    printf("%d ", *p);
}
