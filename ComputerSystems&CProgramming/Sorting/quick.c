#include "quick.h"
int movesQ = 0;
int comparesQ = 0;
// Partitions the given list into two smaller list to sort them
int Partition(int *arr, int left, int right) {
  int pivot = arr[left];
  int lo = left + 1;
  int hi = right;

  while (true) {
    comparesQ += 1;
    while (lo <= hi && arr[hi] >= pivot) {
      comparesQ += 1;
      hi -= 1;
    }

    comparesQ += 1;
    while (lo <= hi && arr[lo] <= pivot) {
      comparesQ += 1;
      lo += 1;
    }

    if (lo <= hi) {
      movesQ += 3;
      int temp = arr[lo];
      arr[lo] = arr[hi];
      arr[hi] = temp;
    } else {
      break;
    }
  }
  movesQ += 3;
  int temp = arr[left];
  arr[left] = arr[hi];
  arr[hi] = temp;
  return hi;
}

// Recursivly calls partition in order to sort using the Quick Sort method
void Quick_sort(int *arr, int left, int right, int size) {

  if (left < right) {
    int index = Partition(arr, left, right);
    Quick_sort(arr, left, index - 1, size);
    Quick_sort(arr, index + 1, right, size);
  }

  return;
}

// Psuedo Code Aquired From Lab Document
