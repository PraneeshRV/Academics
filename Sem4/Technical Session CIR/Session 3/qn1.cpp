// find pair with max difference
// arr = [3, 10, 5, 2, 8, 15]
#include <iostream>
using namespace std;
void maxDifference(int arr[], int n) {
    int maxDiff = 0;
    int firstNum = 0, secondNum = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[j] - arr[i] > maxDiff) {
                maxDiff = arr[j] - arr[i];
                firstNum = arr[i];
                secondNum = arr[j];
            }
        }
    }
    cout << "The pair is: " << firstNum << " and " << secondNum << " with max difference: "<<maxDiff<<endl;
}

int main() {
    int arr[] = {3, 10, 5, 2, 8, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    maxDifference(arr, n);
    return 0;
}
