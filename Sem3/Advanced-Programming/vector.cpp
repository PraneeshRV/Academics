#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> myVector;
    myVector.push_back(10);
    myVector.push_back(20);
    myVector.push_back(30);
    if (myVector.empty()) {
        cout << "Vector is empty."<<endl;
    } else {
        cout << "Vector is not empty."<<endl;
    }
    cout << "First element: " << myVector[0] << endl;
    cout << "Elements of the vector: ";
    for (auto it = myVector.begin(); it != myVector.end(); ++it) {
        cout << *it << " ";  
    }
    cout << endl;

    cout << "Size: " << myVector.size() << endl;
    cout << "Address: " << &myVector << endl;
  
    myVector.clear();
   
    if (myVector.empty()) {
        cout << "Vector is empty after clearing."<<endl;
    } else {
        cout << "Vector is not empty after clearing."<<endl;
    }
    return 0;
}