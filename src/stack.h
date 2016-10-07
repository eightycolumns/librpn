#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct node Stack;

struct node *push(struct node **top_node, const char *string);
char *pop(char *string, struct node **top_node);
char *peek(const struct node *top_node);
bool is_empty(const struct node *top_node);

#endif
