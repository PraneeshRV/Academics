  
#include <stdio.h>

void main() {
    int m, n;
    printf("Enter the number of rows ");
    scanf("%d", &n);
    m = n;
    int count = 1;
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= m - 1; k++)
            printf("  ");
        m--;
        for (int j = 1; j <= i; j++) {
            printf("%d ", count);
            count++;
        }
        printf("\n");
    }
}