#include "stack.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void prin(Stack *s, Stack *e) {
  int disk = stack_peek(s);
  printf("Move disk %d from peg %c to peg %c \n", disk, s->name, e->name);
}

void Hanoi(int disks, Stack *s, Stack *e, Stack *o) {

  if (stack_peek(s) == 0) {
    return;
  }

  else if (disks == 1) {

    prin(s, e);
    int temp = stack_pop(s);
    stack_push(e, temp);
  } else {

    int n = disks - 1;
    Hanoi(n, s, o, e);
    prin(s, e);
    int tempe = stack_pop(s);
    stack_push(e, tempe);
    Hanoi(n, o, e, s);
  }
}

void HanoiIter(int disks, Stack *s, Stack *e, Stack *o) {
  printf("================================\n");
  printf("----------   STACKS   ----------\n");
  printf("================================\n");
  int TotalMoves = pow(2, disks) - 1;

  if (disks % 2 == 0) {

    for (int i = 1; i <= TotalMoves; i++) {

      if (i % 3 == 1) {
        if (((stack_peek(s) < stack_peek(o)) && stack_peek(s) > 0) ||
            (stack_peek(o) < 1 && stack_peek(s) > 0)) {
          prin(s, o);
          int temp = stack_pop(s);
          stack_push(o, temp);

        } else if (((stack_peek(s) > stack_peek(o)) && stack_peek(o) > 0) ||
                   (stack_peek(s) < 1 && stack_peek(o) > 0)) {
          prin(o, s);
          int temp = stack_pop(o);
          stack_push(s, temp);
        }
      }

      if (i % 3 == 2) {
        if (((stack_peek(s) < stack_peek(e)) && stack_peek(s) > 0) ||
            (stack_peek(e) < 1 && stack_peek(s) > 0)) {
          prin(s, e);
          int temp = stack_pop(s);
          stack_push(e, temp);

        } else if (((stack_peek(s) > stack_peek(e)) && stack_peek(e) > 0) ||
                   (stack_peek(s) < 1 && stack_peek(e) > 0)) {
          prin(e, s);
          int temp = stack_pop(e);
          stack_push(s, temp);
        }
      }

      if (i % 3 == 0) {
        if (((stack_peek(e) < stack_peek(o)) && stack_peek(e) > 0) ||
            (stack_peek(o) < 1 && stack_peek(e) > 0)) {
          prin(e, o);
          int temp = stack_pop(e);
          stack_push(o, temp);

        } else if (((stack_peek(e) > stack_peek(o)) && stack_peek(o) > 0) ||
                   (stack_peek(e) < 1 && stack_peek(o) > 0)) {
          prin(o, e);
          int temp = stack_pop(o);
          stack_push(e, temp);
        }
      }
    }
  } else {

    for (int i = 1; i <= TotalMoves; i++) {

      if (i % 3 == 1) {
        if (((stack_peek(s) < stack_peek(e)) && stack_peek(s) > 0) ||
            (stack_peek(e) < 1 && stack_peek(s) > 0)) {
          prin(s, e);
          int temp = stack_pop(s);
          stack_push(e, temp);

        } else if (((stack_peek(s) > stack_peek(e)) && stack_peek(e) > 0) ||
                   (stack_peek(s) < 1 && stack_peek(e) > 0)) {
          prin(e, s);
          int temp = stack_pop(e);
          stack_push(s, temp);
        }
      }

      if (i % 3 == 2) {
        if (((stack_peek(s) < stack_peek(o)) && stack_peek(s) > 0) ||
            (stack_peek(o) < 1 && stack_peek(s) > 0)) {
          prin(s, o);
          int temp = stack_pop(s);
          stack_push(o, temp);

        } else if (((stack_peek(s) > stack_peek(o)) && stack_peek(o) > 0) ||
                   (stack_peek(s) < 1 && stack_peek(o) > 0)) {
          prin(o, s);
          int temp = stack_pop(o);
          stack_push(s, temp);
        }
      }

      if (i % 3 == 0) {
        if (((stack_peek(o) < stack_peek(e)) && stack_peek(o) > 0) ||
            (stack_peek(e) < 1 && stack_peek(o) > 0)) {
          prin(o, e);
          int temp = stack_pop(o);
          stack_push(e, temp);

        } else if (((stack_peek(o) > stack_peek(e)) && stack_peek(e) > 0) ||
                   (stack_peek(o) < 1 && stack_peek(e) > 0)) {
          prin(e, o);
          int temp = stack_pop(e);
          stack_push(o, temp);
        }
      }
    }
  }
}

#define OPTIONS "srn:"
int main(int argc, char **argv) {

  bool recur = false;
  bool stack = false;
  int infile = 0;

  int d = 0;
  while ((d = getopt(argc, argv, OPTIONS)) != -1) {
    switch (d) {

    case 's':
      stack = true;
      break;
    case 'r':
      recur = true;
      break;
    case 'n':
      infile = atoi(optarg);
      break;
    }
  }

  int numDisks = infile;
  if (numDisks == 0) {
    numDisks = 5;
  }

  char a = 'A';
  char b = 'B';
  char c = 'C';

  Stack *A = stack_create(numDisks, a);
  Stack *B = stack_create(numDisks, b);
  Stack *C = stack_create(numDisks, c);

  int i = 0;
  for (i = numDisks; i > 0; i--) {
    stack_push(A, i);
  }

  if (stack) {
    HanoiIter(numDisks, A, B, C);
    int TotalMoves = pow(2, numDisks) - 1;
    printf("\nNumber of moves: %d\n", TotalMoves);
  }

  /*========RESETTING STACKS===========*/
  int x = 0;
  for (x = 0; x < numDisks; x++) {
    stack_pop(B);
  }

  int y = 0;
  for (y = numDisks; y > 0; y--) {
    stack_push(A, y);
  }
  /*====================================*/

  if (recur) {
    printf("================================\n");
    printf("--------   RECURSION   ---------\n");
    printf("================================\n");
    Hanoi(numDisks, A, B, C);
    int TotalMoves = pow(2, numDisks) - 1;
    printf("\nNumber of moves: %d\n", TotalMoves);
  }

  stack_delete(A);
  stack_delete(B);
  stack_delete(C);

  return 0;
}
