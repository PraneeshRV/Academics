#include <stdio.h>

int *getPointer(int *ptr)
{
    return ptr;
}

int main()
{
    int num = 10;
    int *ptr = &num;

        printf("Address of num: %p\n", ptr);

    int *returnedPtr = getPointer(ptr);
    printf("Address returned by getPointer: %p\n", returnedPtr);

    return 0;
}
