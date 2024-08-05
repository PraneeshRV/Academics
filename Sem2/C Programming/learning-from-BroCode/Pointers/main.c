#include <stdio.h> 

void printAge(int *pAge)
{
    printf("You are %d years old", *pAge);  // deference
}

int main()
{
    // pointer = a "variable-like" reference that holds a memory address to another variable, array, etc.
    //           some tasks are performed more easily with pointers 
    //           * = indirection operator (value at address)

    int age = 21;
    int *pAge = NULL;
    pAge = &age; 

    //printf("Address of age: %p\n", &age);
    //printf("Value of pAge: %p\n", pAge);

    //printf("Size of age: %d bytes\n", sizeof(age));
    //printf("Size of pAge: %d bytes\n", sizeof(pAge));

    //printf("Value of age: %d\n", age);
    //printf("Value of stored address: %d\n", *pAge);  // dereferencing the pointer 

    printAge(pAge);

    return 0;
}