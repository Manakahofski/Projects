#ifndef __STACK_H__
#define __STACK_H__

/*#include <tower.c>*/
#include <inttypes.h>
#include <stdbool.h>

typedef struct Stack {
  char name;
  int top;
  int capacity;
  int *items;
} Stack;

Stack *stack_create(int capacity, char name);

void stack_delete(Stack *s);

int stack_pop(Stack *s);

void stack_push(Stack *s, int item);

bool stack_empty(Stack *s);

int stack_peek(Stack *s);

#endif
