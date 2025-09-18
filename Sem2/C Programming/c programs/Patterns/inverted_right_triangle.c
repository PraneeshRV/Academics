// C program to print an inverted right triangle 
#include <stdio.h>

void main()
{
    int rows;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    for(int i = rows; i > 0; i--)
    {
        for(int stars = i; stars > 0; stars--)
        {
            printf("*");
        }   
        
        printf("\n");
    }
}