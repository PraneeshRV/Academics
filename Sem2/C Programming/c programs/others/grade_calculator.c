#include<stdio.h>
void main (){
int s1,s2,s3,s4,s5;
printf("input your marks in 5 subjects\n");
scanf("%d \n %d \n %d \n %d \n %d",&s1,&s2,&s3, &s4,&s5);
int total=s1+s2+s3+s4+s5;
float percent =total/5;
printf("total marks is %d\n",total);
printf("percentage is %f\n",percent);
if(percent>=90)
  printf("grade O");
else if (percent>=80)
  printf("grade A+");
  else if (percent>=70)
    printf("grade A");
  else if (percent>=60)
    printf("grade B+");
  else if (percent>=50)
    printf("grade B");
  else if (percent>=40)
    printf("grade C");
  else 
    printf("grade F");
}