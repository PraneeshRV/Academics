  #include <stdio.h>
  void selectionSort(int arr[], int n) {
      for (int i = 0; i < n-1; i++) {
          int min = i;
          for (int j = i+1; j < n; j++)
              if (arr[j] < arr[min])
                  min = j;
          int temp = arr[min];
          arr[min] = arr[i];
          arr[i] = temp;
      }
  }
  int main() {
      int n = 5;
      int arr[] = {64, 25, 12, 22, 11};
      printf("Original array: ");
      for (int i = 0; i < n; i++)
          printf("%d ", arr[i]);
        
      selectionSort(arr, n);
    
      printf("\nSorted array: ");
      for (int i = 0; i < n; i++)
          printf("%d ", arr[i]);
    
      return 0;
  }
