#include <stdio.h>
int main()
{
    int a[] = {39,22,58,43,11,80};
    int n = sizeof(a) / sizeof(a[0]);
    int i, j, temp;
    printf("Before sorting\n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    for (i = 1; i < n; i++)
    {
        j = i;

        while(j>0 && a[j-1] > a[j])
        {
            temp=a[j];
            a[j] = a[j-1];
            a[j-1]=temp;
            j--;
        }
    }
    printf("\nAfter sorting \n");
    for (i = 0; i < n; i++)
        printf("%d ",a[i]);
    return 0;
}