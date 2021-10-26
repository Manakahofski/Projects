#ifndef __ARRAY_H__
#define __ARRAY_H__
#include "ll.h"
// HEAVY INFLUENCE FROM STACK IMPLEMENTATION OF PREVIOUS LAB AND TUTORIAL FOR
// HOW TO CREATE DYNAMIC INT ARRAYS
// (https://stackoverflow.com/questions/3536153/c-dynamically-growing-array)
typedef struct {
  char **list;
  size_t used;
  size_t size;
} list;

void createList(list *a, size_t size);

void insertList(list *a, char *element);

void freeList(list *a);
#endif
