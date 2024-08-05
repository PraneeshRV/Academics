// Combine two arrays
#include <stdio.h>

int main()
{
    int arr1[100], arr2[100], arr3[200], n1, n2, i;

    printf("Enter the number of elements in the first array: ");
    scanf("%d", &n1);

    printf("Enter the elements in the first array: ");
    for (i = 0; i < n1; i++)
    {
        scanf("%d", &arr1[i]);
    }

    printf("Enter the number of elements in the second array: ");
    scanf("%d", &n2);

    printf("Enter the elements in the second array: ");
    for (i = 0; i < n2; i++)
    {
        scanf("%d", &arr2[i]);
    }

    for (i = 0; i < n1; i++)
    {
        arr3[i] = arr1[i];
    }
    for (i = 0; i < n2; i++)
    {
        arr3[i + n1] = arr2[i];
    }

    printf("The combined array is: ");
    for (i = 0; i < n1 + n2; i++)
    {
        printf("%d ", arr3[i]);
    }

    return 0;
}
