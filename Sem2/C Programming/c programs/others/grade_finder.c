#include <stdio.h>


void main()
{
    float g1, g2, g3, g4, g5;
    float result; 

    printf("Enter percentage of subject 1: ");
    scanf("%f", &g1);

    printf("Enter percentage of subject 2: ");
    scanf("%f", &g2);
    
    printf("Enter percentage of subject 3: ");
    scanf("%f", &g3);

    printf("Enter percentage of subject 4: ");
    scanf("%f", &g4);

    printf("Enter percentage of subject 5: ");
    scanf("%f", &g5);

    result = (g1 + g2 + g3 + g4 + g5) / (float) 5;

    if(result >= 90 && result <= 100)
    {
        char grade[] = "O";
        printf("The grade assigned is: %s and the percentage is: %.2f", grade, result);
    }

    else if(result >= 80 && result < 90)
    {
        char grade[] = "A+";
        printf("The grade assigned is: %s and the percentage is: %.2f", grade, result);
    }

    else if(result >= 70 && result < 80)
    {
        char grade[] = "A";
        printf("The grade assigned is: %s and the percentage is: %.2f", grade, result);
    }

    else if(result >= 60 && result < 70)
    {
        char grade[] = "B+";
        printf("The grade assigned is: %s and the percentage is: %.2f", grade, result);
    }

    else if(result >= 50 && result < 60)
    {
        char grade[] = "B";
        printf("The grade assigned is: %s and the percentage is: %.2f", grade, result);
    }

    else if(result >= 40 && result < 50)
    {
        char grade[] = "C";
        printf("The grade assigned is: %s and the percentage is: %.2f", grade, result);
    }

    else if(result < 40)
    {
        char grade[] = "F";
        printf("The grade assigned is: %s and the percentage is: %.2f", grade, result);
    }

}