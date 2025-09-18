#include <stdio.h>


float SimpleInterest(float p, float n, float r)
{
    return (p*n*r)/(float) 100;
}


int main()
{   
    float principle, years, rate, interest;

    printf("Enter the principle amount: ");
    scanf("%f", &principle);

    printf("Enter the number of years: ");
    scanf("%f", &years);

    printf("Enter the rate of interest: ");
    scanf("%f", &rate);

    interest = SimpleInterest(principle, years, rate);

    printf("The interest is: %.2f\n", interest);
    printf("The total amount is: %.2f", principle + interest);

    return 0;
}