// Deletion of an element from the specified location from an array
#include <stdio.h>

int main()
{
    int arr[100], i, n, pos;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the elements in the array: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the position where you want to delete the element: ");
    scanf("%d", &pos);

    for (i = pos - 1; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    n--;

    printf("The array after deletion is: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
