#include "bf.h"
#include <stdlib.h>

BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter) + 1);
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    bf->size = size;
    return bf;
  }
  return (BloomFilter *)NIL;
}

void bf_delete(BloomFilter *bf) {
  bv_delete(bf->filter);
  free(bf);
}

void bf_insert(BloomFilter *bf, char *key) {

  bv_set_bit(bf->filter, hash(bf->primary, key) % bf->size);

  bv_set_bit(bf->filter, hash(bf->secondary, key) % bf->size);

  bv_set_bit(bf->filter, hash(bf->tertiary, key) % bf->size);
}

bool bf_probe(BloomFilter *bf, char *key) {

  int key1 = bv_get_bit(bf->filter, hash(bf->primary, key) % bf->size);
  int key2 = bv_get_bit(bf->filter, hash(bf->secondary, key) % bf->size);
  int key3 = bv_get_bit(bf->filter, hash(bf->tertiary, key) % bf->size);
  if ((key1 == 1) && (key2 == 1) && (key3 == 1)) {
    return 1;
  } else {
    return 0;
  }
}
