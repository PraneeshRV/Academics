#include <stdio.h>
int increment(int *x) {
return *x++;
}
int main() {
int arr[] = {10, 20, 30};
int temp = increment(&arr[0]);
printf( "%d" ,temp) ;
return 0;
}