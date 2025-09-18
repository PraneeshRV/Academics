#include <stdio.h>

void main()
{
    int x, y, a, b, c;

    a = 2;
    b = 3;
    c = 4;

    printf("Enter x value: ");
    scanf("%d", &x);

    y = (a * x * x) + (b * x) + c;

    printf("y value is: %d\n", y);

}
