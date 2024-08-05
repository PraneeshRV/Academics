#include <stdio.h>
void main(){
int a,b,c,i=0,j,arm=0;
  printf("enter the number\n");
  scanf("%d",&a);
  c=a;
  j=a;
  while (c!=0){
  c=c/10;
  i++;
  }
 while (a!=0){
   b=a%10;
   arm=arm+pow(b,i);
   a=a/10;
 }
  if(j==arm){
    printf("%d is an armstrong number",j);
  }
  else 
    printf("%d is not an armstrong number",j);
}