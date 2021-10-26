#include "ll.h"
#include <string.h>
float links = 0;
float ll_heads = 0;
float ll_length = 0;
ListNode *ll_node_create(HatterSpeak *gs) {
  ll_heads += 1;
  ListNode *l = (struct ListNode *)malloc(sizeof(struct ListNode) + 1);
  l->gs = gs;
  l->next = NULL;
  return l;
}

ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  ll_length += 1;
  ListNode *A = (struct ListNode *)malloc(sizeof(struct ListNode) + 1);
  A->gs = gs;
  A->next = (*head);
  (*head) = A;
  return A;
}

void ll_delete(ListNode *head) {
  ListNode *n = head;
  ListNode *save;
  while (n != NULL) {

    save = n->next;
    free(n->gs);
    free(n);
    n = save;
  }
}

ListNode *ll_lookup(ListNode **head, char *key) {
  ListNode *n = (*head);
  ListNode *prev = NULL;

  while (n != NULL) {
    links += 1;

    if (strcmp(n->gs->oldspeak, key) == 0) {

      if (move_to_front) {
        if (prev != NULL) {
          prev->next = n->next;
          n->next = (*head);
          (*head) = n;
        }
      }

      return n;
    } else {

      prev = n;
      n = n->next;
    }
  }

  return NULL;
}

void ll_node_delete(ListNode *n) {

  ListNode *next = n->next;
  if (next != NULL) {
    n->gs = next->gs;
    n->next = next->next;
    free(next);

  } else {
    free(n);
  }
}

int ll_count(ListNode *head) {
  ListNode *n = head;
  int x = 0;
  while (n != NULL) {
    x += 1;
    n = n->next;
  }
  return x;
}
void ll_print(ListNode *head) {
  ListNode *n = head;
  while (n != NULL) {
    printf("%s %s\n", n->gs->oldspeak, n->gs->hatterspeak);
    n = n->next;
  }
}
