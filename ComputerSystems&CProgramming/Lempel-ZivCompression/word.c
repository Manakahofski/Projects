#include "word.h"
#include "code.h"

// ========= Creates a new word ==========
Word *word_create(uint8_t *syms, uint64_t len) {
  Word *w = (struct Word *)malloc(sizeof(struct Word));
  if (w == NULL) {
    printf("w null\n");
    exit(0);
  }
  w->syms = (uint8_t *)calloc(100, sizeof(uint8_t));
  if (w->syms == NULL) {
    printf("asdasd\n");
    exit(0);
  }
  w->syms = memcpy(w->syms, syms, sizeof(&w->syms));
  w->len = len;
  return w;
}

// ========= Appends a sym to existing word ==========
Word *word_append_sym(Word *w, uint8_t sym) {
  if (sym == 0) {
  }
  Word *aw = (struct Word *)malloc(sizeof(struct Word));
  int x = w->len;
  if (aw == NULL) {
    printf("Memory allocation failed");
    exit(0);
  }
  aw->syms = (uint8_t *)calloc(100, sizeof(uint8_t));
  if (aw->syms == NULL) {
    printf("NULL!\n");
    exit(0);
  }
  if (w->syms == NULL) {
    printf("NULL!!\n");
    exit(0);
  }
  memcpy(aw->syms, w->syms, sizeof(&aw->syms));
  aw->syms[x] = sym;
  aw->len = x + 1;
  return aw;
}

// ========= Deletes a word ==========
void word_delete(Word *w) {
  free(w->syms);
  free(w);
}

// ========= Creates a new word table  ==========
WordTable *wt_create(void) {
  uint8_t empty_word[1] = {0};
  WordTable *wt = calloc(MAX_CODE, sizeof(struct Word));
  if (wt == NULL) {
    printf("wt null\n");
    exit(0);
  }
  wt[EMPTY_CODE] = word_create(empty_word, 0);
  return wt;
}

// ========= Resets a word table ==========
void wt_reset(WordTable *wt) {
  for (int i = 0; i < MAX_CODE; i++) {
    if (wt[i] != 0) {
      word_delete(wt[i]);
      wt[i] = 0;
    }
  }
}

// ========= Deletes a word table ==========
void wt_delete(WordTable *wt) {
  wt_reset(wt);
  free(wt);
}
