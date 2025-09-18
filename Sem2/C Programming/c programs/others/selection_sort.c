#include<stdio.h>
int main()
{
    int a[] = {56,31,24,99,52};
    int n = sizeof(a) / sizeof(a[0]);
    int i, j, temp;
    printf("Before sorting array elements are - \n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    for (i = 0; i < n; i++)
    {
        for (j = i+1; j < n; j++)
        {
         if (a[i] > a[j])
         {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
        }
        }
        }
    printf("\n Enter elements after sorting \n");
    for (i = 0; i < n; i++)
        printf("%d ",a[i]);
    return 0;
}

