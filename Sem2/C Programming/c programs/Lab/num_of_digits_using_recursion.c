// Program to count number of digits using recursion
#include <stdio.h>
int digcount(int n)
{
    static int c = 0;
    if (n>0){
        c++;
        digcount(n/10);
    }
    else{
    return c;
    }
}

int main(){
    int num;
    printf("Enter a positive integer number: ");
    scanf("%d", &num);
    int b = digcount(num);
    printf("Total digits in number %d is: %d\n", num, b);
    return 0;
}
