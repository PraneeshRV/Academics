// find and eliminate duplicates in an array
// arr[] = {2,10,10,100,2,10,11,2,11,2}
#include <iostream>
using namespace std;
int main()
{
    int arr[] = {2, 10, 10, 100, 2, 10, 11, 2, 11, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int duplicates[n];
    int duplicatesCount = 0;
    
    for (int i = 0; i < n; i++)
    {
        bool isDuplicate = false;
        bool alreadyPrinted = false;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                isDuplicate = true;
                break;
            }
        }
        for (int j = 0; j < duplicatesCount; j++)
        {
            if (arr[i] == duplicates[j])
            {
                alreadyPrinted = true;
                break;
            }
        }
        
        if (isDuplicate && !alreadyPrinted)
        {
            duplicates[duplicatesCount] = arr[i];
            duplicatesCount++;
            cout << arr[i] << " ";
        }
    }
    cout << endl;
    return 0;
}