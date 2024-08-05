#include <stdio.h> 

int main()
{
    // for loop = repeats a block of code a limited amount of times

    for(int i = 10; i >= 1; i -= 3)  // for(int counting_var; (condition); increment/decrement)
    {
        printf("%d\n", i);
    }

    return 0; 
}