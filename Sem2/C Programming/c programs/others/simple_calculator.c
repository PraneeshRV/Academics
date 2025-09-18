#include<stdio.h>
int main ()
{
  int num1, num2;
  float result;
  char ch;
  printf ("Enter first number\n");
  scanf ("%d", &num1);
  printf ("Enter second number\n");
  scanf ("%d", &num2);
  printf ("Choose operator to perform operations(+,-,*,/,%)\n");
  scanf (" %c", &ch);
  result = 0;
  switch (ch)
    {
    case '+':
      result = num1 + num2;
      break;
    case '-':
      result = num1 - num2;
      break;
    case '*':
      result = num1 * num2;
      break;
    case '/':
      result = num1 / num2;
      break;
      case '%' :
      result = num1 % num2;
      break;
    default:
      printf ("Invalid operation\n");
    }
  printf ("Result: %d %c %d = %f\n", num1, ch, num2, result);
  return 0;
}