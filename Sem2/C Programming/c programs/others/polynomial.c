// C program to calculate the value of a polynomial for a given input. 

#include <stdio.h>
#include <math.h> 

void main()
{
    int a = 2, b = 3, c = 4;
    float x, result; 

    printf("Enter value: ");
    scanf("%f", &x);

    result = (a * (pow(x, 2))) + (b * x) + c;

    printf("The result is: %.2f", result);

}