//find subarray with given sum 
//arr, 2, 3, 7, 5], sum = 12
#include <iostream>
using namespace std;
int main()
{
    int arr[] = {2, 3, 7, 5};
    int sum = 12;
    int n = sizeof(arr) / sizeof(arr[0]);
    int currentSum = arr[0];
    int start = 0;
    for (int i = 1; i <= n; i++)
    {
        while (currentSum > sum && start < i - 1)
        {
            currentSum -= arr[start];
            start++;
        }
        if (currentSum == sum)
        {
            cout << "Subarray elements: [ ";
            
            for(int j = start; j < i; j++) {
                cout << arr[j] << " ";
            }
            cout <<"]"<< endl;            
            return 0;
        }
        if (i < n)
        {
            currentSum += arr[i];
        }
    }
    cout << "No subarray found" << endl;
    return 0;
}