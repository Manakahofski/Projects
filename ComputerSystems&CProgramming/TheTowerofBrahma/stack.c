#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack *stack_create(int size, char name) {
  struct Stack *s = (struct Stack *)malloc(sizeof(struct Stack));
  s->capacity = size;
  s->top = 0;
  s->name = name;
  if (!s) {
    return NULL;
  }
  if (size < 1) {
    size = 1;
  }

  s->items = (int *)malloc(sizeof(int) * size);
  if (!s->items) {
    return NULL;
  }

  return s;
}

void stack_push(Stack *s, int i) {
  if (!s) {
    return;
  }
  if (s->top == s->capacity) {
    s->capacity *= 2;
    s->items = (int *)realloc(s->items, s->capacity * sizeof(int));
  }
  if (s->items) {
    s->items[s->top] = i;
    s->top += 1;
  }
  return;
}

int stack_pop(Stack *s) {
  if (!s) {
    return -1;
  }
  if (s->top > 0) {
    s->top -= 1;
    return s->items[s->top];

  } else {
    return -1;
  }
}

bool stack_empty(Stack *s) { return s->top == 0; }

int stack_peek(Stack *s) {
  if (s->top == 0) {
    return 0;
  } else {
    return s->items[s->top - 1];
  }
}

void stack_delete(Stack *s) {
  free(s->items);
  free(s);
  return;
}
