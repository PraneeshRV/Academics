// C program to print a pyramid with spaces
#include <stdio.h>

void main()
{

    int rows; 

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    for(int i = 1; i <= rows; i++)
    {
        for(int spaces = rows - i; spaces > 0; spaces--)
        {
            printf(" ");
        }

        for(int stars = 1; stars <= i; stars++)
        {
            printf("* ");
        }


        printf("\n");
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       