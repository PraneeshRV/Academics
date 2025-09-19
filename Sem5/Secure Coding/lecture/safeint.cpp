#include <iostream>
#include <limits.h>
#include "SafeInt.hpp"

using namespace std;

int main(){
    int a = INT_MAX;
    int b = 1;
    int c;
    cout << c << endl;
    if (SafeAdd(a, b, c)) {
        cout << "Result: " << c << endl;
    } else {
        cout << "Overflow occurred!" << endl;
    }
    return 0;
}