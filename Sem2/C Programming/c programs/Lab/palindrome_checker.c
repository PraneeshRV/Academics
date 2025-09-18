// Program to check number palindrome or not using recursion
#include <stdio.h>
int pali(int num);
int main(){
    int num;
    printf("Enter any number: ");
    scanf("%d", &num);
    if (pali(num))
        printf("%d is a palindrome number.\n", num);
    else
        printf("%d is not a palindrome number.\n", num);
    return 0;
}
int pali(int num)
{
    static int ogNum;
    if (num == ogNum)
        return 1;
    else if (num < 0)
        return 0;
    int lastdig = num % 10;
    ogNum = ogNum * 10 + lastdig;
    return pali(num / 10);
}
