#include<stdio.h>
int main()
{
    int a[] = {23,43,51,22,44};
    int n = sizeof(a) / sizeof(a[0]);
    int i, j, temp;
    printf("Before \n");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    for (i = 0; i < n - 1;i++)
    {
    for (j=0;j<n-i-1;j++)
    {
      if (a[j]>a[j+1])
      {
        int temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
}
printf("\n After Sorting \n");
    for (i = 0; i < n; i++)
        printf("%d ",a[i]);
}
