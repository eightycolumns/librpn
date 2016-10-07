#include "src/stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct node {
  char *string;
  struct node *next_node;
};

struct node *push(struct node **top_node, const char *string) {
  assert(top_node != NULL);
  assert(string != NULL);

  struct node *new_node = malloc(sizeof(struct node));

  if (new_node == NULL) {
    return NULL;
  }

  new_node->string = malloc(strlen(string) + 1);

  if (new_node->string == NULL) {
    return NULL;
  }

  strcpy(new_node->string, string);
  new_node->next_node = *top_node;

  *top_node = new_node;

  return *top_node;
}

char *pop(char *string, struct node **top_node) {
  assert(string != NULL);
  assert(top_node != NULL);

  if (*top_node == NULL) {
    return NULL;
  }

  strcpy(string, (*top_node)->string);
  struct node *temp_node = (*top_node)->next_node;

  free((*top_node)->string);
  free(*top_node);

  *top_node = temp_node;

  return string;
}

char *peek(const struct node *top_node) {
  if (top_node == NULL) {
    return NULL;
  }

  return top_node->string;
}

bool is_empty(const struct node *top_node) {
  return top_node == NULL;
}
