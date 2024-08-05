// C program to find the prime numbers in a given range. 

#include <stdio.h>

void main()
{
    for(int i = 2; i < 100; i++)
    {
        int cnt = 2;

        for(int j = 2; j < i; j++)
        {
            if(i % j == 0)
            {
                cnt++; 
            }
        }

        if(cnt <= 2)
        {
            printf("%d\n", i);
        }
    }
}