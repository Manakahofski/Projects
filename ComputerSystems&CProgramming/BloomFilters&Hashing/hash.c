//
// Constructor for a HashTable .

//
// length : Length of the HashTable .
// salt : Salt for the HashTable .
//
#include "hash.h"
float seeks = 0;
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable) + 1);
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }

  return (HashTable *)NIL;
}

// The rest of the functions you must implement yourselves .

void ht_delete(HashTable *ht) {
  for (unsigned int i = 0; i < ht->length; i++) {
    ll_delete(ht->heads[i]);
  }
  free(ht->heads);
  free(ht);
}

uint32_t ht_count(HashTable *h) {
  int x = 0;
  for (unsigned int i = 0; i < h->length; i++) {
    if (h->heads[i] != NULL) {
      x += 1;
    }
  }
  return x;
}

ListNode *ht_lookup(HashTable *ht, char *key) {
  seeks += 1;
  uint32_t index = hash(ht->salt, key) % ht->length;

  void *x = ll_lookup(&ht->heads[index], key);
  if (x != NULL) {
    return x;
  } else {
    return NULL;
  }
}

void ht_insert(HashTable *ht, HatterSpeak *gs) {
  seeks -= 1;
  links -= 1;
  if (ht_lookup(ht, gs->oldspeak) == NULL) {
    uint32_t index = hash(ht->salt, gs->oldspeak) % ht->length;
    if (ht->heads[index] != NULL) {
      ll_insert(&ht->heads[index], gs);
    } else {
      ListNode *node = ll_node_create(gs);
      ht->heads[index] = node;
    }
  }
}
