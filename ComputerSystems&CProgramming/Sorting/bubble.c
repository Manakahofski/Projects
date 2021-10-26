#include "bubble.h"
// Takes an array and the array size as inputs and sorts it in a Bubble Sort
// method
void Bubble_sort(int *arr, int size) {
  printf("Bubble Sort\n");
  int moves = 0;
  int compares = 0;
  int j = 0;
  for (int i = 0; i <= size - 1; i++) {
    j = size - 1;
    while (j > i) {
      compares += 1;
      if (arr[j] < arr[j - 1]) {
        moves += 3;
        int temp = arr[j];
        arr[j] = arr[j - 1];
        arr[j - 1] = temp;
      }
      j -= 1;
    }
  }
  printf("%d elements, %d moves, %d compares\n", size, moves, compares);
  return;
}

// Psuedo Code Aquired From Lab Document
