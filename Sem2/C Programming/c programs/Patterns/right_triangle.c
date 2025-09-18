// C program to print a right triangle 
#include <stdio.h>

void main()
{
    int rows; 

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    for(int i = 1; i <= rows; i++)
    {
        for(int stars = 1; stars <= i; stars++)
        {   
            printf("*");
        }
        
        printf("\n");
    }
}