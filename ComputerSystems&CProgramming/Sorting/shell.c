#include "shell.h"
int length = 0;

// Generates a list of gaps for the Shell sort function given the length of the
// list
int *gap(int size) {
  int *g = (int *)calloc(size, sizeof(int));
  int i = 0;
  int n = size;
  while (n > 1) {
    if (n <= 2) {
      n = 1;
    } else {
      n = floor(5 * n / 11);
    }
    g[i] = n;
    i += 1;
    length += 1;
  }

  return g;
}

// Sorts a list of given length usng the Shell Sort method
void Shell_sort(int *arr, int size) {
  printf("Shell Sort \n");
  int *tmpAr = gap(size);
  int compares = 0;
  int moves = 0;
  for (int y = 0; y < length; y++) {
    int step = tmpAr[y];
    for (int i = step; i < size; i++) {
      for (int j = i; j > step - 1; j -= step) {
        compares += 1;
        if (arr[j] < arr[j - step]) {
          moves += 3;
          int temp = arr[j];
          arr[j] = arr[j - step];
          arr[j - step] = temp;
        }
      }
    }
  }
  printf("%d elements, %d moves, %d compares\n", size, moves, compares);
  free(tmpAr);
  return;
}

// Psuedo Code Aquired From Lab Document
