#include "bv.h"
#include "sieve.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>

/* ========================== PRINT FORMAT FOR PRIMES ==================*/
void printA(BitVector *A, BitVector *B, BitVector *C, BitVector *D) {
  for (uint32_t i = 2; i < A->length; i++) {
    if (bv_get_bit(A, i) == 1) {
      printf("%d: prime", i);
    }
    if (bv_get_bit(D, i) == 1) {
      printf(", mersenne");
    }
    if (bv_get_bit(C, i) == 1) {
      printf(", lucas");
    }
    if (bv_get_bit(B, i) == 1) {
      printf(", fibonacci");
    }
    if (bv_get_bit(A, i) == 1) {
      printf("\n");
    }
  }
}

/*===============================================================*/

/* ========================= Fibonnaci Check ======================*/

// Checks if Perfect Square
bool isPerfectSquare(int x) {
  int s = sqrt(x);
  return (s * s == x);
}

// Fib Check
void fib(BitVector *P) {
  for (uint32_t i = 0; i < P->length; i++) {
    int x = bv_get_bit(P, i);
    if (x == 1) { // If prime, check if fib number
      int tmp = (5 * i * i + 4);
      int tmp2 = (5 * i * i - 4);
      if (isPerfectSquare(tmp) || isPerfectSquare(tmp2)) {
        ;
      } else { // if not fib number, change bit to 0
        bv_clr_bit(P, i);
      }
    } else {
      ;
    }
  }
}
/*==============================================================*/

/* ========================= Lucas Check ======================*/
void luc(BitVector *P) {
  for (uint32_t i = 0; i < P->length; i++) {
    int x = bv_get_bit(P, i);
    if (x == 1) { // If prime, compare to generator
      // Help understanding lucas generator from
      // https://www.geeksforgeeks.org/lucas-numbers/
      uint32_t a = 2;
      uint32_t b = 1;
      uint32_t c = 0;
      while (i > b) {
        c = a + b;
        a = b;
        b = c;
      }
      if (i != b && i != 2 && i != 1) { // if not lucas number, change bit to 0
        bv_clr_bit(P, i);
      }
    }
  }
}

/*==============================================================*/

/* ========================= Mersenne Check ======================*/
void mer(BitVector *P) {
  for (uint32_t i = 0; i < P->length; i++) {
    int x = bv_get_bit(P, i);
    if (x == 1) { // If prime, compare to generator
      int n = 0;
      uint32_t test = 0;
      // Help understanding generator from WolframMathWorld
      while (test < i) {
        test = pow(2, n) - 1;
        n += 1;
      }
      if (test > i) { // if not mer number, change bit to 0
        bv_clr_bit(P, i);
      }
    }
  }
}

/*==============================================================*/

/* ============================= Palindrome Function ======================*/
void cnvrtbase(BitVector *P, int b) {
  for (uint32_t i = 2; i < P->length; i++) {
    int x = bv_get_bit(P, i);
    int result = i;
    int remain = 0;
    char arrayDic[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                       'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                       'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's'};
    char arrayNum[30];
    int turn = 0;

    if (x == 1) { // If Prime

      while (result > 0) { // Performs Base change and stores in arrayNum
        remain = result % b;
        result = result / b;

        arrayNum[turn] = arrayDic[remain];
        turn += 1;
      }
      bool prin = 1;
      for (int j = turn; j > 0; j--) { // checks both ends of arrayNum at same
                                       // time. If equal, prin = true
        prin = (arrayNum[j - 1] == arrayNum[turn - j]);

        if (!prin) {

          break;
        }
      }
      if (prin) { // If prin is true, prints palindrome
        printf("%d = ", i);
        for (int j = turn; j > 0; j--) {
          int q = arrayNum[j - 1];
          printf("%c", q);
        }
        printf("\n");
      }
    }
  }
}
  /*=============================================================================*/

  /* ====================================== MAIN
   * ===============================*/

#define OPTIONS "spn:"
int main(int argc, char **argv) {
  /*=============== Get Arguments ============*/
  bool prime = false;
  bool palin = false;
  int infile = 0;
  int d = 0;
  while ((d = getopt(argc, argv, OPTIONS)) != -1) {
    switch (d) {

    case 's':
      prime = true;
      break;
    case 'p':
      palin = true;
      break;
    case 'n':
      infile = atoi(optarg);
      break;
    }
  }

  int num = infile;
  if (num == 0) {
    num = 1000;
  }
  /*================================================*/

  /*========================= -s ====================*/
  if (prime) {
    // Initialize all BitVectors required
    BitVector *A = bv_create(num);
    bv_set_all_bits(A);
    sieve(A);
    BitVector *B = bv_create(num);
    bv_set_all_bits(B);
    sieve(B);
    BitVector *C = bv_create(num);
    bv_set_all_bits(C);
    sieve(C);
    BitVector *D = bv_create(num);
    bv_set_all_bits(D);
    sieve(D);
    // Perform the "Interesting Prime" Functions
    fib(B);
    luc(C);
    mer(D);
    // Hand BitVectors to printA for formatting
    printA(A, B, C, D);
    // Clear mem
    bv_delete(A);
    bv_delete(B);
    bv_delete(C);
    bv_delete(D);
  }
  /* ======================================================*/

  /*========================== -p =======================*/
  if (palin) {
    // Initialize BitVector required
    BitVector *A = bv_create(num);
    bv_set_all_bits(A);
    sieve(A);
    // print header and perform base change and palidrome print
    printf("Base  2\n");
    printf("---- --\n");
    cnvrtbase(A, 2);
    printf("\n");
    printf("Base  9\n");
    printf("---- --\n");
    cnvrtbase(A, 9);
    printf("\n");
    printf("Base 10\n");
    printf("---- --\n");
    cnvrtbase(A, 10);
    printf("\n");
    printf("Base 28\n");
    printf("---- --\n");
    cnvrtbase(A, 28);
    printf("\n");
    // clear mem
    bv_delete(A);
  }
}
/*=======================================================*/

/*=============================================================================*/
