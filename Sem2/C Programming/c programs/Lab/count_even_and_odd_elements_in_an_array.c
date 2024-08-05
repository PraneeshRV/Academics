// Program to count even and odd elements in an array.
#include <stdio.h>

int main()
{
    int arr[100];
    int i, size, even = 0, odd = 0;

    printf("Enter size of the array: ");
    scanf("%d", &size);

    printf("Enter %d elements in the array: ", size);
    for (i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            even++;
        }
        else
        {
            odd++;
        }
    }
    printf("Total even elements: %d\n", even);
    printf("Total odd elements: %d", odd);

    return 0;
}
