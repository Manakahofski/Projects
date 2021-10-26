
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
  read_header(infile, &h);
  if (h.magic != 0x8badbeef) {
    printf("Magic Number Didnt Match!\n");
    return 0;
  }
  /*====================== Encode Logic =============*/
  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;
  while (read_pair(infile, &curr_code, &curr_sym, bit_length(next_code))) {
    table[next_code] =
        word_append_sym(table[curr_code], curr_sym); // Create new word
    buffer_word(outfile, table[next_code]);          // Buffer word
    next_code = next_code + 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);
  wt_delete(table);

  if (stats) {
    printf("Compressed file size: %.0f bytes\n", reads);
    printf("Uncompressed file size: %.0f bytes\n", writes);
    printf("Compression ratio: %.2f%%\n", 100 * (1 - (reads / writes)));
  }
}
