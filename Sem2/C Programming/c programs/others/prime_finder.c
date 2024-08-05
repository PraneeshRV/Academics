#include <stdio.h>
void main(){
int a,i,j=0;
  printf("enter the number\n");
  scanf("%d",&a);
if (a==1)
  printf("1 is neither prime nor composite");
  else {
  for(i=1;i<a;i++){
    if(a%i==0){
      j++;
    }
  }
  if (j==1){
    printf("%d is a prime number",a);
  }
    else {
    printf("%d is not a prime number",a);
    }
  }
}