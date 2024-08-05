#include <stdio.h> 

double square(double x)  // we precede the type of return value before the function name 
{
    return x * x; 
}

int main()
{   
    double x = square(3.14); 
    printf("%lf", x); 

    return 0;
}