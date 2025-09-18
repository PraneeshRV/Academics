//Fibonacci series
#include <stdio.h>
void main(){
int a,b,c,i,j;
  printf("enter the first two numbers of the series\n");
  scanf("%d %d",&a,&b);
  printf("enter the number of terms\n");
  scanf("%d",&i);
  printf("%d\t %d\t",a,b);
  c=a+b;
  for (j=1;j<=i-2;j++) {
    printf("%d\t",c);
    a=b;
    b=c;
    c=a+b;
  }
}