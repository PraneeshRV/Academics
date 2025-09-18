//To find a specific term in the standard fibonacci series using recursion
#include <stdio.h>
int fibonum(int);
void main(){
    int a,b;
    printf("enter n value: ");
    scanf("%d",&a);
    b=fibonum(a);
    printf("%d",b);
}
int fibonum(int a){
    if (a==0)
    return 0;
    else if (a==1)
    return 1;
    else 
    return fibonum(a-1) + fibonum(a-2);
}