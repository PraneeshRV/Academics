#include <stdio.h> 
#include <math.h> 

int main()
{
    double A = sqrt(9);
    double B = pow(2, 4);
    int C = round(3.14);
    int D = ceil(3.14);
    int E = floor(3.99); 
    double F = fabs(-100);
    double G = log(3); //same as ln(3) with base "e" 
    double H = sin(45); //angle is in radians
    double I = cos(45); 
    double J = tan(45);

    printf("\n%lf", A);
    printf("\n%lf", B);
    printf("\n%d", C);
    printf("\n%d", D);
    printf("\n%d", E);
    printf("\n%lf", F);
    printf("\n%lf", G);
    printf("\n%lf", H);
    printf("\n%lf", I);
    printf("\n%lf", J);

}