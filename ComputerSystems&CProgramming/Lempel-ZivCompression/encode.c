#include "io.h"
#include "trie.h"
#include "word.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTIONS "vi:o:"

int main(int argc, char **argv) {
  /*=============== Get Arguments ============*/
  bool stats = false;
  bool givenIn = false;
  bool givenOut = false;
  char *infiler = "none";
  char *outfiler = "none";
  int d = 0;
  while ((d = getopt(argc, argv, OPTIONS)) != -1) {
    switch (d) {
    case 'v':
      stats = true;
      break;
    case 'i':
      givenIn = true;
      infiler = optarg;
      break;
    case 'o':
      givenOut = true;
      outfiler = optarg;
      break;
    }
  }
  /*====================== Open Files =============*/
  int infile;
  int outfile;
  if (givenIn) {
    infile = open(infiler, O_RDONLY);
    if (infile < 0) {
    }
  } else {
    infile = STDIN_FILENO;
  }
  if (givenOut) {
    outfile = open(outfiler, O_WRONLY | O_CREAT | O_TRUNC);
  } else {
    outfile = STDOUT_FILENO;
  }

  /*====================== Verify Header =============*/

  struct FileHeader h;
  struct stat temp;
  fstat(infile, &temp);
  h.magic = 0x8badbeef;
  h.protection = temp.st_mode;
  write_header(outfile, &h);

  /*====================== Encode Logic =============*/
  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;
  TrieNode *next_node;
  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;
  int count = 0;
  while (read_sym(infile, &curr_sym)) {
    count += 1;
    next_node = trie_step(curr_node, curr_sym); // Branch Tree
    if (next_node != NULL) {                    // If tree exist
      prev_node = curr_node;
      curr_node = next_node;
    } else { // If doesnt exist
      buffer_pair(outfile, curr_node->code, curr_sym, bit_length(next_code));
      curr_node->children[curr_sym] = trie_node_create(next_code);
      curr_node = root;
      next_code = next_code + 1;
    }
    if (next_code == MAX_CODE) { // If reached max
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
    prev_sym = curr_sym;
  }
  if (curr_node != root) { // Aslong as its not the root
    buffer_pair(outfile, prev_node->code, prev_sym, bit_length(next_code));
    next_code = (next_code + 1) % MAX_CODE;
  }
  buffer_pair(outfile, STOP_CODE, 0,
              bit_length(next_code)); // Put in last words
  flush_pairs(outfile);               // Send to output
  trie_delete(root);

  if (stats) {
    printf("Compressed file size: %.0f bytes\n", writes);
    printf("Uncompressed file size: %.0f bytes\n", reads);
    printf("Compression ratio: %.2f%%\n", 100 * (1 - (writes / reads)));
  }
}
