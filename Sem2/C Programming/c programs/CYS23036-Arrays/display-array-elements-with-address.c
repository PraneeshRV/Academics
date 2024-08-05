// Display array elements with an address
#include <stdio.h>

int main()
{
    int arr[5], i;

    printf("Enter 5 elements in the array: ");
    for (i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Array elements and their addresses:\n");
    for (i = 0; i < 5; i++)
    {
        printf("Element = %d, Address = %p\n", arr[i], &arr[i]);
    }

    return 0;
}