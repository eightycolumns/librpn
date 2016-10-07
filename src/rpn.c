#include "src/rpn.h"

#include <string.h>

#include "src/stack.h"

int infix_to_postfix(char *postfix, const char *infix) {
  if (postfix == NULL || infix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  strcpy(postfix, "");

  Stack *stack = NULL;

  for (size_t i = 0; i < strlen(infix); i += 1) {
    char token[2];
    strncpy(token, infix + i, 1);
    token[1] = '\0';

    if (
      strcmp("a", token) == 0 ||
      strcmp("b", token) == 0 ||
      strcmp("c", token) == 0
    ) {
      strcat(postfix, token);
    } else if (
      strcmp("+", token) == 0 ||
      strcmp("-", token) == 0
    ) {
      if (!is_empty(stack)) {
        char operator[2];
        pop(operator, &stack);
        strcat(postfix, operator);
      }

      push(&stack, token);
    }
  }

  char operator[2];
  pop(operator, &stack);
  strcat(postfix, operator);

  return RPN_SUCCESS;
}

int postfix_to_infix(char *infix, const char *postfix) {
  if (infix == NULL || postfix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  return RPN_SUCCESS;
}
