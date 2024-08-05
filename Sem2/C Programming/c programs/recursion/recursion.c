#include <stdio.h>
void print(int n);
int main(){
    print(5);
    return 0;

}

void print(int n){

    if(n<=1){
        return;
    }
    print(n - 1);
    printf("%d", n);
}