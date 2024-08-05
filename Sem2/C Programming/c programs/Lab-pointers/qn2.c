#include <stdio.h>
int main()
{
    float a = 13.5;
    float *b, *c;
    b = &a;
    c = b;
    printf("\n%f %u %u", a, b, c);
    printf("\n%f %f %f %f %f", a, *(&a), *&a, *b, *c);
    return 0;
}
