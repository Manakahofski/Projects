#include "trie.h"
// ========= Creates a starting Trie Node ==========
TrieNode *trie_node_create(uint16_t code) {
  TrieNode *t = (struct TrieNode *)malloc(sizeof(struct TrieNode));
  // TrieNode *children[ALPHABET];
  t->code = code;
  if (t->code == 0) {
    printf("t null\n");
    exit(0);
  }
  for (int i = 0; i < ALPHABET; i++) {
    t->children[i] = 0;
  }
  return t;
}

// ========= Deletes a trie node ==========
void trie_node_delete(TrieNode *n) { free(n); }

// ========= Creates a new Trie ==========
TrieNode *trie_create(void) {
  TrieNode *t = (struct TrieNode *)malloc(sizeof(struct TrieNode));
  t->code = EMPTY_CODE;
  if (t->code == 0) {
    printf("t null\n");
    exit(0);
  }
  for (int i = 0; i < ALPHABET; i++) {
    t->children[i] = 0;
  }
  return t;
}

// ========= Resets a trie ==========
void trie_reset(TrieNode *root) {
  for (int i = 0; i < ALPHABET; i++) {
    if (root->children[i] != 0) {
      trie_delete(root->children[i]);
      root->children[i] = 0;
    }
  }
}

// ========= Deletes an entire trie ==========
void trie_delete(TrieNode *n) {
  for (int i = 0; i < ALPHABET; i++) {
    if (n->children[i] != 0) {
      trie_delete(n->children[i]);
    }
  }
  trie_node_delete(n);
}

// ========= Steps through a trie ==========
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  if (n->children[sym] != 0) {
    return n->children[sym];
  } else {
    return NULL;
  }
}
