#include <stdio.h>

void sort(int ar[], int size)
{
for(int i = 0;i<size - 1;i++){
    for(int j =0;j<size-1;j++){

        if (ar[j]>ar[j+1]){
                int temp = ar[j];
                ar[j]=ar[j+1];
                ar[j+1]=temp;
        }
    }
}
}
void printArray(int ar[],int size){
    for(int i = 0; i <size-1;i++){
        printf("%d ",ar[i]);
    }
}

int main()
{    
int ar[] = {1,4,76,5,3,2,63,19,20};
int size = sizeof(ar) / sizeof(ar[0]);
sort(ar,size);
printArray(ar,size);
    return 0;
}