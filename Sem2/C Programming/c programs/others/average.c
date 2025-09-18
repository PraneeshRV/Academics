#include <stdio.h>

int main()
{
    int a;
    int b;
    int c;

    printf("Enter the first number: ");
    scanf("%d", &a);

    printf("Enter the second number: ");
    scanf("%d", &b);

    printf("Enter the third number: ");
    scanf("%d", &c);

    float res = (a + b + c)/ (float) 3;
    // to get the decimal portion of the answer, 
    // we should type-cast the divisor to a float

    printf("The average of %d, %d and %d is: %f", a, b, c, res);

    return 0;
}