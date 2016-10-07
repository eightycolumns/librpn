#include "src/rpn.h"

#include <assert.h>
#include <string.h>

#include "src/stack.h"

static char *copy_substring(char *dest, const char *src, size_t n);

int infix_to_postfix(char *postfix, const char *infix) {
  if (postfix == NULL || infix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  strcpy(postfix, "");

  Stack *stack = NULL;

  for (size_t i = 0; i < strlen(infix); i += 1) {
    char token[2];
    copy_substring(token, infix + i, 1);

    if (
      strcmp("a", token) == 0 ||
      strcmp("b", token) == 0 ||
      strcmp("c", token) == 0
    ) {
      strcat(postfix, token);
    } else if (
      strcmp("+", token) == 0 ||
      strcmp("-", token) == 0 ||
      strcmp("*", token) == 0 ||
      strcmp("/", token) == 0
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

static char *copy_substring(char *dest, const char *src, size_t n) {
  assert(dest != NULL);
  assert(src != NULL);
  assert(n <= strlen(src));

  strncpy(dest, src, n);
  dest[n] = '\0';

  return dest;
}
