//Search an element in an array
#include <stdio.h>
    int
    main()
{
    int arr[100], i, n, key, found = 0;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    printf("Enter the elements in the array: ");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element you want to search: ");
    scanf("%d", &key);

    for (i = 0; i < n; i++)
    {
        if (arr[i] == key)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("Element found at position: %d\n", i + 1);
    }
    else
    {
        printf("Element not found in the array.\n");
    }

    return 0;
}
