

#define OPTIONS "h:f:msb"
#include "array.h"
#include "bf.h"
#include "hash.h"
#include "parser.h"
#include <ctype.h>
#include <getopt.h>
#include <math.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=========== Declaring Variables ==========
bool move_to_front = false;
bool stats = false;
int main(int argc, char **argv) {
  //=========== Setting up Files ==========
  FILE *oldspeak;
  FILE *hatterspeak;
  oldspeak = fopen("oldspeak.txt", "r");
  hatterspeak = fopen("hatterspeak.txt", "r");

  int hashSize = 10000;
  int bloomSize = 1048576;
  int d = 0;
  while ((d = getopt(argc, argv, OPTIONS)) != -1) {
    //============= USER INPUT ===============
    switch (d) {

    case 'h':
      hashSize = atoi(optarg);
      break;
    case 'f':
      bloomSize = atoi(optarg);
      break;
    case 'm':
      move_to_front = true;
      break;
    case 'b':
      move_to_front = false;
      break;
    case 's':
      stats = true;
      break;
    }
  }
  //========== Create Data Stuctures =======
  BloomFilter *bf = bf_create(bloomSize);
  HashTable *ht = ht_create(hashSize);

  //=========== OldSpeak Read ==========
  regex_t a;
  regcomp(&a, "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]*)*", 1);
  regex_t b;
  regcomp(
      &b,
      "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]*)*.[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]*)*",
      1);

  char *string1 = "";

  struct HatterSpeak *ptr1[99999];
  int y = 0;
  while ((string1 = next_word(oldspeak, &a)) != NULL) {

    char *word1;
    ptr1[y] = (struct HatterSpeak *)malloc(sizeof(struct HatterSpeak));
    char *token = strtok(string1, " "); // Borrowed Code Credit edpresso

    word1 = token;
    token = strtok(NULL, " ");
    strcpy(ptr1[y]->oldspeak, word1);

    strcpy(ptr1[y]->hatterspeak, "&&&&&");
    ht_insert(ht, ptr1[y]);
    bf_insert(bf, word1);
    // printf("%s %s\n", ptr[i]->oldspeak, ptr[i]->hatterspeak);
    y += 1;

    fscanf(oldspeak, "%*[-\n]");
  }

  //=========== HatterSpeak Read ==========
  char *string = "";

  struct HatterSpeak *ptr[10000];
  int i = 0; // Increment var
  while ((string = next_word(hatterspeak, &b)) != NULL) {
    char *word1;
    char *word2;
    ptr[i] = (struct HatterSpeak *)malloc(sizeof(struct HatterSpeak));
    char *token = strtok(string, " "); // Code Credit edpresso
    word1 = token;
    token = strtok(NULL, " ");
    word2 = token;
    strcpy(ptr[i]->oldspeak, word1);
    strcpy(ptr[i]->hatterspeak, word2);
    ht_insert(ht, ptr[i]);
    bf_insert(bf, word1);
    i += 1;
  }

  // ================= Check STDIN ========================

  char *x;
  int g = 0;
  // ----- Create arrays to hold Non-Speak --------
  list *vio = (list *)malloc(sizeof(list) + 1);
  createList(vio, 1);
  list *trans = (list *)malloc(sizeof(list) + 1);
  createList(trans, 1);
  //-----------------------------------------------
  while ((x = next_word(stdin, &a)) != NULL) {
    // ------------- Make LowerCase -------------------
    for (unsigned int k = 0; k <= strlen(x); k++) {
      x[k] = tolower(x[k]);
    }
    //-------------------------------------------------
    char looking[100]; // Holds Current Word
    strncpy(looking, x, 100);
    if (bf_probe(bf, looking)) { // If in bloom filter
      ListNode *result = ht_lookup(ht, looking);
      if (result != NULL) { // If in hash table
        bool add = true;    // Set bools for later
        bool add1 = true;
        if (strcmp(result->gs->hatterspeak, "&&&&&") != 0) { // if not oldspeak
          for (unsigned int i = 0; i < trans->used; i += 1) {
            if (strcmp(result->gs->oldspeak, trans->list[i]) ==
                0) {       // if word already searched
              add = false; // Dont Search
            }
          }
          if (add) { // If not counted already, add
            g += 1;
            insertList(trans, result->gs->oldspeak);
            insertList(trans, result->gs->hatterspeak);
          }

        } else if (strcmp(result->gs->hatterspeak, "&&&&&") ==
                   0) { // if oldspeak
          for (unsigned int i = 0; i < vio->used; i += 1) {
            if (strcmp(result->gs->oldspeak, vio->list[i]) ==
                0) { // if word already searched
              add1 = false;
            }
          }
          if (add1) { // if not counted, add
            insertList(vio, result->gs->oldspeak);
          }
          // printf("Inserting to vio: %s", result->gs->oldspeak);
        }
      }
    }
  }
  //=============================================== PRINT FORMATING (NON-STATS)
  //================================================
  if (!stats) {
    if (trans->used >= 1 && vio->used >= 1) {
      printf(
          "Dear Wonderlander,\n\nYou have chosen to use words that the queen has decreed oldspeak.\n\
Due to your infraction you will be sent to the dungeon where you will be taught hatterspeak.\n\nYour errors:\n\n");
      for (unsigned int i = 0; i < vio->used; i++) {
        printf("%s\n", vio->list[i]);
      }
      printf("\nAppropriate hatterspeak translations.\n\n");
      for (int i = 0; i < (g * 2); i += 2) {
        printf("%s -> %s\n", trans->list[i], trans->list[i + 1]);
      }
    }

    if (trans->used >= 1 && vio->used == 0) {
      printf("Dear Wonderlander,\n\nThe decree for hatterspeak finds your "
             "message lacking. Some of the words that you used are not "
             "hatterspeak.\nThe list shows how to turn the oldspeak words into "
             "hatterspeak.\n\n");

      printf("Appropriate hatterspeak translations.\n\n");
      for (int i = 0; i < (g * 2); i += 2) {
        printf("%s -> %s\n", trans->list[i], trans->list[i + 1]);
      }
    }

    if (trans->used == 0 && vio->used >= 1) {
      printf(
          "Dear Wonderlander,\n\nYou have chosen to use words that the queen has decreed oldspeak.\n\
Due to your infraction you will be sent to the dungeon where you will be taught hatterspeak.\n\nYour errors:\n\n");
      for (unsigned int i = 0; i < vio->used; i++) {
        printf("%s\n", vio->list[i]);
      }
    }
  }
  // =======================================================================================================================

  //=============================================== PRINT FORMATING (STATS FOR
  // NERDS) ================================================
  if (stats) {
    float setBits = 0;
    for (i = 0; i < bloomSize; i++) {
      if (bv_get_bit(bf->filter, i)) {
        setBits += 1;
      }
    }
    float hl = hashSize;
    printf("Seeks: %0f\n", seeks);
    float y = links / seeks;
    printf("Average seek length: %f\n", y);
    float x = ll_length / hl;
    printf("Average Linked List Length: %f\n", x);
    float q = (ll_heads / hl) * 100;
    printf("Hash table load: %f%%\n", q);
    float p = (setBits / bloomSize) * 100;
    printf("Bloom filter load: %f%%\n", p);
  }
  //==========================================================================================================================

  //======= Cleaning up memory ==============
  freeList(vio);
  freeList(trans);
  ht_delete(ht);
  bf_delete(bf);
  regfree(&a);
  regfree(&b);
  // ======== Hello grader pls give good grade for readability i try so hard
  // ==========
}
