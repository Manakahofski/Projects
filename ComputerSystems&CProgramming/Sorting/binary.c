#include "binary.h"
int movesB = 0;
int comparesB = 0;
// Sorts a list of given length using the Binary Insertion method
void Binary_Insertion_Sort(int *arr, int size) {
  for (int i = 0; i < size; i++) {
    int value = arr[i];
    int left = 0;
    int right = i;

    while (left < right) {
      int mid = left + floor(((right - left) / 2));
      comparesB += 1;
      if (value >= arr[mid]) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }

    for (int j = i; j > left; j -= 1) {
      movesB += 3;
      int temp = arr[j - 1];
      arr[j - 1] = arr[j];
      arr[j] = temp;
    }
  }
  return;
}

// Psuedo Code Aquired From Lab Document
