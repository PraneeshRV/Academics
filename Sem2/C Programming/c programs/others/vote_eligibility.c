#include <stdio.h>

int main()
{
    int age;
    printf("Enter your age: ");
    scanf("%d", &age);

    if(age >= 0)
    {
        if(age >= 18)
        {
            printf("Eligible to vote.");
        }

        else
        {
            printf("Not eligible to vote.");
        }
    }

    else
    {
        printf("Enter a valid age.");
    }

    return 0;
}
