// C++ program to change all letters of a string to the following letter in the English alphabet
// example: a -> b, b -> c, z -> a, A -> B, B -> C, Z -> A
#include <iostream>
#include <string>
using namespace std;

string changeLetters(string str) {
    for(int i = 0; i < str.length(); i++) {
        if((str[i] >= 'a' && str[i] < 'z') || (str[i] >= 'A' && str[i] < 'Z')) {
            str[i] = str[i] + 1;
        }
        else if(str[i] == 'z') {
            str[i] = 'a';
        }
        else if(str[i] == 'Z') {
            str[i] = 'A';
        }
    }
    return str;
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);
    
    string result = changeLetters(input);
    cout << "Modified string: " << result << endl;
    
    return 0;
}
