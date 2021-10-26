#ifndef __TRIE_H__
#define __TRIE_H__

#include "code.h"
#include <inttypes.h>
#define ALPHABET 256
#include <stdio.h>
#include <stdlib.h>
typedef struct TrieNode TrieNode;

struct TrieNode {
  TrieNode *children[ALPHABET];
  uint16_t code;
};

TrieNode *trie_node_create(uint16_t code);

void trie_node_delete(TrieNode *n);

TrieNode *trie_create(void);

void trie_reset(TrieNode *root);

void trie_delete(TrieNode *n);

TrieNode *trie_step(TrieNode *n, uint8_t sym);

#endif