#include <stdio.h> 

void main()
{
    int a1, a2, a3;

    scanf("%d", &a1);
    scanf("%d", &a2);
    scanf("%d", &a3);


    if(a1 + a2 + a3 == 180)
    {
        if(a1 == a2 && a1 == a3 && a2 == a3)
        {
            printf("It's an equilateral triangle\n");
        }

        else if((a1 == a2 && a1 == a3) || 
                (a2 == a1 && a2 == a3) || 
                (a3 == a1 && a3 == a2))

        {
            printf("It's an isosceles triangle\n");
        }

        else
        {
            printf("It's a scalene triangle\n");
        }

        if(a1 < 90 && a2 < 90 && a3 < 90)
        {
            printf("It's an acute triangle\n");
        }

        else if(a1 == 90 || a2 == 90 || a3 == 90)
        {
            printf("It's a right triangle\n");
        }

        else if(a1 > 90 || a2 > 90 || a3 > 90)
        {
            printf("It's an obtuse triangle\n");
        }
    }

    else
    {
        printf("The triangle is not valid!");
    }
}