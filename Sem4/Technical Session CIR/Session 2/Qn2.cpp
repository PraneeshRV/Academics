/* given array of distinct elements of size N, the task is to rearrange the elements of the array in a
 zig-zag fashion, ie., the elements are arranged as smaller, then larger, then smaller and so on.
 so that the converted array should be in the below form: arr[0]<arr[1]>arr[2]<arr[3]> and so on. 
 example input {4,3,7,8,6,2,1} example output {3,7,4,8,2,6,1} 3 <7> 4 <8> 2 <6> 1 */

#include <iostream>
using namespace std;
int main(){
     int n;
         cout << "Enter size of array: ";
         cin >> n;
         
         int arr[n];
         cout << "Enter " << n << " distinct elements: ";
         for(int i=0; i<n; i++) {
             cin >> arr[i];
         }

         for(int i=0; i<n-1; i++) {
             for(int j=0; j<n-i-1; j++) {
                 if(arr[j] > arr[j+1]) {
                     int temp = arr[j];
                     arr[j] = arr[j+1];
                     arr[j+1] = temp;
                 }
             }
         }
         
         for(int i=1; i<n-1; i+=2) {
             int temp = arr[i];
             arr[i] = arr[i+1];
             arr[i+1] = temp;
        }
         
              cout << "Zigzag array: ";
              for(int i=0; i<n; i++) {
                  cout << arr[i];
                  if(i < n-1) {
                      if(i % 2 == 0) cout << " <";
                      else cout << "> ";
                  }
              }
     
}