#include <iostream>
#include "SafeInt.hpp" 
using namespace std;
int main() {
    int x, y;
    char op;
    cout << "Enter first integer: ";
    cin >> x;
    cout << "Enter operator (+ - * /): ";
    cin >> op;
    cout << "Enter second integer: ";
    cin >> y;

    SafeInt<int> a(x), b(y), result;

    try {
        switch(op) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            default:
                std::cout << "Invalid operator!" << std::endl;
                return 1;
        }
        cout << "Result: " << static_cast<int>(result) << endl;
    } catch (SafeIntException&) {
        cout << "Error: Invalid operation (overflow or divide by zero)" << endl;
    }
    return 0;
}