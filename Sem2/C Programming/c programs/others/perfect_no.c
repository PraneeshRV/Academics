// C program to check whether a number is a perfect number or not. 
#include <stdio.h>

int main()
{
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    int sum = 0;

    for(int i = 1; i < n; ++i)
    {
        if(n % i == 0)
        {
            sum += i;
        }
    }

    if(sum == n)
    {
        printf("The number is a perfect number");
    }

    else
    {
        printf("The number is not perfect");
    }

}