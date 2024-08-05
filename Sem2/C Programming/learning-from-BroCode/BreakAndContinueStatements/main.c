#include <stdio.h> 

int main()
{
    // continue = skips rest of the code & forces the next iteration of the loop
    // break = exits a loop/switch

    for(int i = 1; i <= 20; i++)
    {
        if(i == 13)
        {
            break;
        }
        printf("%d\n", i);
    }

    return 0; 
}