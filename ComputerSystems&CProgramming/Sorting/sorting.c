#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "Aiqsbp:r:n:"
//= FORMATS SORT PRINT =======================
void printN(int NumPrint, int *a) {
  for (int i = 1; i < NumPrint + 1; i++) {
    printf("%13u", a[i - 1]);
    if (i % 7 == 0 && i != 0) {
      printf("\n");
    }
  }
  printf("\n");
  return;
}
//= END PRINT FUNCTION =======================

// = Copies myArray to given array ===========
void copyAr(int *a, int *b, int size) {
  for (int i = 0; i < size; i++) {
    a[i] = b[i];
  }
}

int main(int argc, char **argv) {
  // = Define bools and ints for my cases ====================================
  bool bubble = false;
  bool print = false;
  bool shell = false;
  bool quick = false;
  bool binary = false;
  int NumPrint = 100;
  int Seed = 8222022;
  int size = 100;
  // = End Define Bools ======================================================

  // = Parse Command Line For Arguments ======================================
  int d = 0;
  while ((d = getopt(argc, argv, OPTIONS)) != -1) {

    switch (d) {
    case 'A':
      binary = true;
      quick = true;
      shell = true;
      bubble = true;
      break;

    case 'i':
      binary = true;
      break;

    case 'q':
      quick = true;
      break;

    case 's':
      shell = true;
      break;

    case 'b':
      bubble = true;
      break;

    case 'p':
      print = true;
      NumPrint = atoi(optarg);
      break;

    case 'r':
      Seed = atoi(optarg);
      break;

    case 'n':
      size = atoi(optarg);
      break;
    }
  }
  // = End Command Line Parse ================================================

  // = Handling Edge Cases ===================================================
  if (size == 0) {
    printf("Nothing to Sort!\n");
    return 0;
  }

  if (NumPrint > size) {
    printf("Cant Print More Than You Have!\n");
    return 0;
  }

  // = Initialize array with random values from given seed ===================
  int *myArray = (int *)calloc(size + 1, sizeof(int));
  srand(Seed);
  for (int i = 1; i <= size + 1; i++) {
    myArray[i - 1] = rand() & 0x3FFFFFFF;
  }
  // = End Initialize ========================================================

  // = Run tests if asked for ================================================
  if (binary) {
    printf("Binary Insertion Sort\n");
    int *b = (int *)calloc(size, sizeof(int));
    copyAr(b, myArray, size);
    Binary_Insertion_Sort(b, size);
    printf("%d elements, %d moves, %d compares\n", size, movesB, comparesB);
    printN(NumPrint, b);
    free(b);
  }

  if (quick) {
    printf("Quick Sort\n");
    int *b = (int *)calloc(size, sizeof(int));
    copyAr(b, myArray, size);
    Quick_sort(b, 0, size - 1, size);
    printf("%d elements, %d moves, %d compares\n", size, movesQ, comparesQ);
    printN(NumPrint, b);
    free(b);
  }

  if (shell) {
    int *b = (int *)calloc(size, sizeof(int));
    copyAr(b, myArray, size);
    Shell_sort(b, size);
    printN(NumPrint, b);
    free(b);
  }

  if (bubble) {
    int *b = (int *)calloc(size, sizeof(int));
    copyAr(b, myArray, size);
    Bubble_sort(b, size);
    printN(NumPrint, b);
    free(b);
  }
  // = End Run tests =========================================================

  free(myArray);
}
