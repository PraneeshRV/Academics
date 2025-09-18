// Insert an element in an array
#include <stdio.h>
int main()
{
    int arr[100] = {0};
    int i, n, pos, val;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the elements in the array: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the position where you want to insert the element: ");
    scanf("%d", &pos);

    printf("Enter the value you want to insert: ");
    scanf("%d", &val);

    for (i = n; i >= pos; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[pos - 1] = val;
    n++;

    printf("The array after insertion is: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
