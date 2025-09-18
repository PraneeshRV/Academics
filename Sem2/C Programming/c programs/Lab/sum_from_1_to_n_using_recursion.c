// Program to calculate the sum of numbers from 1 to n using recursion
#include <stdio.h>
int sumofdigits(int n){
    if (n <= 1)
        return n;
    return n + sumofdigits(n - 1);
}
int main(){
    int n;
    printf("enter the natural number upto which you need the sum: ");
    scanf("%d",&n);
    printf("%d",sumofdigits(n));
    return 0;
}