#include "array.h"
// HEAVY INFLUENCE FROM STACK IMPLEMENTATION OF PREVIOUS LAB AND TUTORIAL FOR
// HOW TO CREATE DYNAMIC INT ARRAYS
// (https://stackoverflow.com/questions/3536153/c-dynamically-growing-array)
void createList(list *a, size_t size) {
  a->list = malloc(size * sizeof(char *));
  a->used = 0;
  a->size = size;
}

void insertList(list *a, char *element) {
  if (a->used == a->size) {
    a->size += 2;
    a->list = realloc(a->list, a->size * sizeof(char *));
  }
  a->list[a->used++] = element;
}

void freeList(list *a) {
  free(a->list);
  a->list = NULL;
  free(a);
}
