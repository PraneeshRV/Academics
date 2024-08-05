// A C program to print the even numbers till 100.

#include <stdio.h>

int main()
{
    int i = 0;
    while(i < 100)
    {
        if(i % 2 == 0)
        {
            printf("%d\n", i);
        }

        i++;
    }

    return 0;
}