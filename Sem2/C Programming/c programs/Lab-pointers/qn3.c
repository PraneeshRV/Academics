#include <stdio.h>
int main()
{
    int value_array[] = {141, 1032};
    int *point;
    int max = 2;
    int a = 0;
    point = value_array;
    while (point <= &value_array[max - 1])
    {
        printf("TechVidvan Tutorial: Pointer Comparison!\n\n");
        printf("Value of value_array[%d] = %d\n", a, *point);
        printf("Address of value_array[%d] = %p\n", a, point);
        point++;
        a++;
    }
    return 0;
}
