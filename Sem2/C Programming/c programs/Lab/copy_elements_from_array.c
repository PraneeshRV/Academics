`// Program to copy elements of one array to another
#include <stdio.h>

int main()
{
    int s;

    printf("Enter the array size: ");
    scanf("%d", &s);

    int a1[s];
    int a2[s];

    printf("Enter the array elements: ");
    for (int i = 0; i < s; i++)
    {
        scanf("%d", &a1[i]);
    }

    for (int j = 0; j < s; j++)
    {
        a2[j] = a1[j];
    }

    printf("Copied array (a2): ");
    for (int k = 0; k < s; k++)
    {
        printf("%d ", a2[k]);
    }

    return 0;
}
