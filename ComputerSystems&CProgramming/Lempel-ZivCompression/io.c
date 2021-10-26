#include "io.h"
uint8_t BUFFER[BLOCK];
float reads;
float writes;
// ========= Reads Header ==========
void read_header(int infile, FileHeader *header) {
  read(infile, header, sizeof(FileHeader));
  reads += sizeof(FileHeader);
}

// ========= Write header ==========
void write_header(int outfile, FileHeader *header) {
  fchmod(outfile, header->protection);
  write(outfile, header, sizeof(FileHeader));
  writes += sizeof(FileHeader);
}

// ========= Reads from the infile ==========
int read_bytes(int infile) {
  int rbytes = 0;
  int total = 0;
  int Need4Read = BLOCK;
  int prev = 0;
  while ((rbytes = read(infile, BUFFER, Need4Read)) > 0) {
    prev = rbytes;
    total += rbytes;
    if (total == BLOCK) {
      reads += BLOCK;
      return -1;
    }
    Need4Read = BLOCK - total;
  }
  reads += prev;
  return prev;
}

int point = BLOCK;
bool fail = true;
int x;
// ========= Returns symbols from buffer when called ==========
bool read_sym(int infile, uint8_t *sym) {
  if (fail) {
    if (point == BLOCK) {
      x = read_bytes(infile);
      if (x >= 0) {
        fail = false;
      }
      point = 0;
    }
  }
  *sym = BUFFER[point];
  point += 1;
  if (fail == false && point - 1 >= x) {
    return false;
  }
  return true;
}

// ========= Finds length of Int ==========
int bit_length(uint16_t code) { return (int)log2(code) + 1; }

uint8_t BUFFEROUT[BLOCK];
int point2;
int loc = 7;
// ========= Buffers a sym pair and code for writing ==========
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  int bit;
  for (int i = 0; i < bitlen; i++) {
    if (point2 == 4096) {
      write(outfile, BUFFEROUT, BLOCK);
      writes += BLOCK;
      // memset(BUFFEROUT, 0, sizeof(BUFFER)); // It would be proper to clear
      // the buffer after each use, but it wont match the tests if i do
      point2 = 0;
      loc = 7;
    }
    bit = (code >> i) & 1u;
    if (bit == 1) {
      BUFFEROUT[point2] |= 1UL << (7 - loc);
    } else {
      BUFFEROUT[point2] &= ~(1UL << (7 - loc));
    }
    loc -= 1;
    if (loc == -1) {
      point2 += 1;
      loc = 7;
    }
  }
  for (int i = 0; i < 8; i++) {
    if (point2 == 4096) {
      write(outfile, BUFFEROUT, BLOCK);
      writes += BLOCK;
      // memset(BUFFEROUT, 0, sizeof(BUFFER)); // It would be proper to clear
      // the buffer after each use, but it wont match the tests if i do
      point2 = 0;
      loc = 7;
    }
    bit = (sym >> i) & 1u;
    if (bit == 1) {
      BUFFEROUT[point2] |= 1UL << (7 - loc);
    } else {
      BUFFEROUT[point2] &= ~(1UL << (7 - loc));
    }
    loc -= 1;
    if (loc == -1) {
      point2 += 1;
      loc = 7;
    }
  }
}

// ========= flushes whats left of the buffer ==========
void flush_pairs(int outfile) {
  if (loc < 7) {
    point2 += 1;
  }
  writes += point2;
  write(outfile, BUFFEROUT, point2);
}

int lo = 7;
// ========= Buffers a sym pair and code for reading ==========
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {
  int bit;
  *code = 0;
  for (int i = 0; i < bitlen;
       i++) { // First buffers the code using the given bitlength, and adjust
              // the pointers to do so
    if (point == 4096) {
      lo = 7;
      point = 0;
      x = read_bytes(infile);
      if (x >= 0) {
        fail = false;
      }
    }
    if (fail == false && point == x - 1) {
      return false;
    }
    bit = (BUFFER[point] >> (7 - lo)) & 1u;
    if (bit == 1) {
      *code |= 1UL << (i);
    } else {
      *code &= ~(1UL << (i));
    }
    lo -= 1;
    if (lo == -1) {
      point += 1;
      lo = 7;
    }
  }
  *sym = 0;
  for (int i = 0; i < 8; i++) { // Now reads the sym that came with the code
    if (point == 4096) {
      lo = 7;
      point = 0;
      x = read_bytes(infile);
      if (x >= 0) {
        fail = false;
      }
    }
    if (fail == false && point == x - 1) {
      return false;
    }
    bit = (BUFFER[point] >> (7 - lo)) & 1u;
    if (bit == 1) {
      *sym |= 1UL << (i);
    } else {
      *sym &= ~(1UL << (i));
    }
    lo -= 1;
    if (lo == -1) {
      point += 1;
      lo = 7;
    }
  }
  if (fail == false && point == x) {
    return false;
  }
  return true;
}

int yeet = 0;
// ========= Buffers a word writing ==========
void buffer_word(int outfile, Word *w) {
  for (uint32_t i = 0; i < w->len; i++) {
    if (yeet == BLOCK) {
      writes += BLOCK;
      write(outfile, BUFFEROUT, BLOCK);
      memset(BUFFEROUT, 0, sizeof(BUFFER));
      yeet = 0;
    }
    BUFFEROUT[yeet] = w->syms[i];
    yeet += 1;
  }
}

// ========= flushes remaining word ==========
void flush_words(int outfile) {
  writes += yeet;
  write(outfile, BUFFEROUT, yeet);
}
