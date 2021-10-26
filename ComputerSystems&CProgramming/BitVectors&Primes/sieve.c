#include "sieve.h"

// NOT FROM LAB DOCUMENT, MADE WITH KNOWLEDGE FROM
// https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
void sieve(BitVector *P) {
  uint32_t l = 0;
  // For all numbers l from 2 to sqrt n
  for (l = 2; l <= sqrt(P->length); l++) {
    // If not changed it prime
    if (bv_get_bit(P, l) == 1) {
      uint32_t i = 0;
      for (i = l * l; i <= (P->length); i += l) {
        bv_clr_bit(P, i);
      }
    }
  }
}
