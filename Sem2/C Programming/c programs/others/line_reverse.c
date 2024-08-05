#include<stdio.h>
#define EOLN '\n'
void reverse();
int main()
{
        printf("Enter the line to reverse\n");
        reverse();
}
void reverse()
{
        char c;
        if((c=getchar())!=EOLN)
                reverse();

        putchar(c);
}