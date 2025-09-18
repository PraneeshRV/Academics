// Find largest element in an array
#include <stdio.h>

int main()
{
    int arr[100], i, n, max;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the elements in the array: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    max = arr[0];
    for (i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    printf("The largest element in the array is: %d\n", max);

    return 0;
}
