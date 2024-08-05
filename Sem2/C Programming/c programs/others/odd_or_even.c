#include <stdio.h>
 
int main()
{
    int num; 
    printf("Enter a number: ");
    scanf("%d", &num);

    if (num % 2 == 0 && num >= 0)
    {
        printf("Number %d is even", num);
    }

    else if (num < 0)
    {
        printf("Number %d is less than zero", num);
    }

    else
    {
        printf("Number %d is odd", num);
    }

    return 0;
}