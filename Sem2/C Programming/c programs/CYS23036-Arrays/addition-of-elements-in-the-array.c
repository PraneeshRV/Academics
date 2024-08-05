// Calculate addition of elements in array
#include <stdio.h>

int main()
{
    int arr[100], i, n, sum = 0;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the elements in the array: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    printf("The sum of the elements in the array is: %d\n", sum);

    return 0;
}
