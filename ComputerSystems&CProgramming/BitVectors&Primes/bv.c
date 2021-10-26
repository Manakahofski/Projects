
#include "bv.h"

// Most functions stolen from my previous code for stack implementation in the
// Hanoi lab asgn3
BitVector *bv_create(uint32_t bit_len) {

  struct BitVector *v = (struct BitVector *)malloc(sizeof(struct BitVector));

  v->length = bit_len;

  int x = ceil(bit_len / 8);

  v->vector = (uint8_t *)malloc(sizeof(uint8_t) * x);

  return v;
}

void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
  return;
}

//
// Returns the length in bits of the BitVector.
//
// v : The BitVector.
//
uint32_t bv_get_len(BitVector *v) { return (v->length); }

//
// Sets the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to set.

void bv_set_bit(BitVector *v, uint32_t i) {

  v->vector[i / 8] = v->vector[i / 8] | (1UL << i % 8);
}

//
// Clears the bit at index in the BitVector.
//
// v : The BitVector.
// i : Index of the bit to clear.
//
void bv_clr_bit(BitVector *v, uint32_t i) {

  v->vector[i / 8] = (v->vector[i / 8] & ~(1UL << i % 8));
} //
// Gets a bit from a BitVector.
//
// v : The BitVector.
// i : Index of the bit to get.
//
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  int prin = (v->vector[i / 8] >> i % 8) & 1u;
  return prin;
}

//
// Sets all bits in a BitVector.
//
// v : The BitVector.
//
void bv_set_all_bits(BitVector *v) {
  for (int x = 0; x < ceil(v->length / 8); x++) {

    v->vector[x] = ~(v->vector[x] & 0);
  }
}
