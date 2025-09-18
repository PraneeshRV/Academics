#include <stdio.h>
#include <math.h>

int main()
{
    int angle1, angle2, angle3;
    int sum;
    int type;

    printf("Enter three angles of triangle: \n");
    scanf("%d %d %d", &angle1, &angle2, &angle3);

    sum = angle1 + angle2 + angle3;

    if (sum == 180 && angle1 > 0 && angle2 > 0 && angle3 > 0)
    {
        printf("Triangle is valid.\n");

        if (angle1 == angle2 && angle2 == angle3)
        {
            type = 1; 
        }
        else if (angle1 == angle2 || angle2 == angle3 || angle1 == angle3)
        {
            type = 2; 
        }
        else
        {
            type = 3;
        }
        switch (type)
        {
            case 1:
                printf("It is an equilateral triangle.\n");
                break;
            case 2:
                printf("It is an isosceles triangle.\n");
                break;
            case 3:
                printf("It is a scalene triangle.\n");
                break;
        }

        if (angle1 == 90 || angle2 == 90 || angle3 == 90)
        {
            printf("It is a right angled triangle.\n");
        }
        else if (angle1 > 90 || angle2 > 90 || angle3 > 90)
        {
            printf("It is an obtuse angled triangle.\n");
        }
        else
        {
            printf("It is an acute angled triangle.\n");
        }
    }
    else
    {
        printf("Triangle is not valid.\n");
    }

    return 0;
}
