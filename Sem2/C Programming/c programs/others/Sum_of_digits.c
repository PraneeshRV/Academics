#include <stdio.h>
void main(){
int a,b,sum=0;
  printf("enter the number\n");
  scanf("%d",&a);
  while (a!=0){
  b=a%10;
  sum=sum+b;
  a=a/10;
  }
  printf("%d",sum);
}