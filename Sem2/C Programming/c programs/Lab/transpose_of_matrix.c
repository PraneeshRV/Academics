// Program to transpose matrix
#include <stdio.h>

void transpose(int matrix[10][10], int row, int col)
{
    int transposed[10][10];

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            transposed[j][i] = matrix[i][j];
        }
    }

    printf("Transpose of the matrix:\n");
    for (int i = 0; i < col; ++i)
    {
        for (int j = 0; j < row; ++j)
        {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int matrix[10][10];
    int row, col;

    printf("Enter rows and columns: ");
    scanf("%d %d", &row, &col);
    printf("\nEnter matrix elements:\n");
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            printf("Enter element a%d%d: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nEntered matrix:\n");
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            printf("%d ", matrix[i][j]);
            if (j == col - 1)
            {
                printf("\n");
            }
        }
    }
    transpose(matrix, row, col);
    return 0;
}