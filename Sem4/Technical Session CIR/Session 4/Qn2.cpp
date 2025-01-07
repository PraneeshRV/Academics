//c++ program to sort characters in a string excluding numbers and symbols
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool isAlphabet(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int main() {
    string str;
    cout << "Enter a string: ";
    getline(cin, str);
    
    // Extract only alphabets
    string alphabets = "";
    for(char c : str) {
        if(isAlphabet(c)) {
            alphabets += c;
        }
    }
    sort(alphabets.begin(), alphabets.end());
    int j = 0;
    for(int i = 0; i < str.length(); i++) {
        if(isAlphabet(str[i])) {
            str[i] = alphabets[j++];
        }
    }
    
    cout << "Sorted string (only alphabets): " << str << endl;
    return 0;
}
