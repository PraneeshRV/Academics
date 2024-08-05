// A C program to check whether a number is a palindrome or not.

#include <stdio.h>

int main()
{
    int num;
    int temp;
    int rev;
    scanf("%d", &num);

    temp = num;
    rev = 0;

    while(num > 0)
    {
        rev = rev*10 + (num % 10);
        num = num / 10;
    }

    if(rev == temp)
    {
        printf("The number is a palindrome!");
    }

    else
    {
        printf("The number is not a palindrome!");
    }

    return 0;
}