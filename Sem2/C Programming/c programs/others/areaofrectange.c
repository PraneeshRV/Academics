#include <stdio.h> 

// Function to calculate the area of a rectangle 


int areaOfRect(int length, int breadth)
{
    int area; 
    area = length * breadth; 
    return area; 
}


int main()
{
    int l, b;

    printf("Enter the length of the rectangle: ");
    scanf("%d", &l);

    printf("Enter the breadth of the rectangle: ");
    scanf("%d", &b);

    int area = areaOfRect(l, b);

    printf("%d", area);

    return 0;
}