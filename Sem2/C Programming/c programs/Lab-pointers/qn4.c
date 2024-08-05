#include <stdio.h>
void display(int *val);
int main()
{
    int a;
    display(&a);
    printf("TechVidvan Tutorial: Passing pointers to function!\n\n");
    printf("Value is: %d\n", a);
    return 0;
}
void display(int *val)
{
    *val = 1002;
    return;
}