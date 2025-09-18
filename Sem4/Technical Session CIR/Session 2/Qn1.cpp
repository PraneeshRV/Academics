// write a program to find all elements in an array of integers that have at least two greater elements than itself

#include <iostream>
using namespace std;
int main(){
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;
    int arr[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i<n; i++){
        cin >> arr[i];
    }
    cout << "The elements that have at least two greater elements than itself are: ";
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[i] < arr[j])
            {
                count++;
            }
        }
        if(count >= 2)
        {
            cout << arr[i] << " ";
        }
    }
}