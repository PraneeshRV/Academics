#include <stdio.h> 

int main()
{   
    // memory = an array of bytes within RAM (street)
    // memory block = a single unit (byte) within memory, used to hold some value (person)
    // memory address = the address of where a memory block is located (house address)

    char a; 
    double b[3];
   
    printf("%d bytes\n", sizeof(a));
    printf("%d bytes\n", sizeof(b));

    // the format specifier for a memory address is %p

    printf("%p\n", &a);  // the memory addresses are in hexadecimal
    printf("%p\n", &b);


    return 0;
}