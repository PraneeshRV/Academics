// find second  largest element in an array without sorting
// arr[]=[12,35,1,10,34,1]
#include <iostream> 
using namespace std;
int main(){
    int arr[] = {12,35,1,10,34,1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int largest = arr[0];
    int secondLargest = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > largest)
        {
            secondLargest = largest;
        }
        else if (arr[i] > secondLargest && arr[i] != largest)
        {
            secondLargest = arr[i];
        }
    }
        cout << "Second largest element is: " << secondLargest << endl;
    }