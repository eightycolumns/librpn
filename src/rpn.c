#include "src/rpn.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "src/stack.h"
#include "src/token.h"
#include "src/util.h"

static int precedence_of(const char *operator);
static bool stack_takes_precedence(const Stack *stack, const char *operator);
static bool is_left_associative(const char *operator);
static bool is_right_associative(const char *operator);

int infix_to_postfix(char *postfix, const char *infix) {
  if (postfix == NULL || infix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  strcpy(postfix, "");

  Stack *stack = NULL;

  for (size_t i = 0; i < strlen(infix); i += 1) {
    char token[2];
    copy_substring(token, infix + i, 1);

    if (is_operand(token)) {
      strcat(postfix, token);
    } else if (is_operator(token)) {
      while (stack_takes_precedence(stack, token)) {
        char operator[2];
        pop(operator, &stack);
        strcat(postfix, operator);
      }

      push(&stack, token);
    }
  }

  while (!is_empty(stack)) {
    char operator[2];
    pop(operator, &stack);
    strcat(postfix, operator);
  }

  return RPN_SUCCESS;
}

int postfix_to_infix(char *infix, const char *postfix) {
  if (infix == NULL || postfix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  return RPN_SUCCESS;
}

static int precedence_of(const char *operator) {
  assert(operator != NULL);

  if (strcmp("^", operator) == 0) {
    return 3;
  } else if (strcmp("*", operator) == 0 || strcmp("/", operator) == 0) {
    return 2;
  } else if (strcmp("+", operator) == 0 || strcmp("-", operator) == 0) {
    return 1;
  } else {
    return 0;
  }
}

static bool stack_takes_precedence(const Stack *stack, const char *operator) {
  assert(operator != NULL);

  if (!is_empty(stack) && is_left_associative(operator)) {
    return precedence_of(peek(stack)) >= precedence_of(operator);
  }

  if (!is_empty(stack) && is_right_associative(operator)) {
    return precedence_of(peek(stack)) > precedence_of(operator);
  }

  return false;
}

static bool is_left_associative(const char *operator) {
  assert(operator != NULL);

  return (
    strcmp("+", operator) == 0 ||
    strcmp("-", operator) == 0 ||
    strcmp("*", operator) == 0 ||
    strcmp("/", operator) == 0
  );
}

static bool is_right_associative(const char *operator) {
  assert(operator != NULL);
  return strcmp("^", operator) == 0;
}
