#include <stdio.h>

int main()
{
    /* escape sequence = character combination consisting of a backslash \
                         followed by a letter or combination of digits.
                         They specify actions within a linr or string of text.
                         \n = newline
                         \t = tab
                         \" = double quote
                         \' = single quote/apostrophe
                         \\ = backslash
    */

    printf("Hello\nWorld\n");
    printf("1\t2\t3\n4\t5\t6\n7\t8\t9\n");  // we can use this to print a matrix structure
    printf("\"I like pizza!\" - Abraham Lincoln probably\n");
    printf("Printing a backslash: \\");
    
    return 0;
}