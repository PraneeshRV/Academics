#include <stdio.h>

int main()
{
    // variable = Allocated space in memory to store a value.
    //            We refer to a variable's name to access the stored value.
    //            That variable now behaves as if it was the value it contains.
    //            BUT we need to declare what type of data we are storing. 

    int x;        // declaration of variable
    x = 123;      // initialization of variable
    int y = 321;  // declaration + initialization of variable

    int age = 21;         // integer
    float gpa = 2.05;     // floating point number 
    char grade = 'C';     // single character
    char name[] = "Bro";  // array of characters (kinda like strings in Python)


    printf("Hello %s\n", name);
    printf("You are %d years old\n", age);  
    printf("Your average grade is %c\n", grade);
    printf("Your gpa is %f\n", gpa);

    // We have to specify the data type here, %s is a placeholder for the
    // value and 's' stands for string, 'd' stands for decimal, 'c' for char
    // and 'f' for float
    
    return 0;
}