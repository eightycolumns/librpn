#include "src/rpn.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "src/stack.h"

static char *copy_substring(char *dest, const char *src, size_t n);
static bool is_operand(const char *token);
static bool is_operator(const char *token);
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

static char *copy_substring(char *dest, const char *src, size_t n) {
  assert(dest != NULL);
  assert(src != NULL);
  assert(n <= strlen(src));

  strncpy(dest, src, n);
  dest[n] = '\0';

  return dest;
}

static bool is_operand(const char *token) {
  assert(token != NULL);

  return (
    strcmp("a", token) == 0 ||
    strcmp("b", token) == 0 ||
    strcmp("c", token) == 0 ||
    strcmp("d", token) == 0 ||
    strcmp("e", token) == 0 ||
    strcmp("f", token) == 0
  );
}

static bool is_operator(const char *token) {
  assert(token != NULL);

  return (
    strcmp("+", token) == 0 ||
    strcmp("-", token) == 0 ||
    strcmp("*", token) == 0 ||
    strcmp("/", token) == 0 ||
    strcmp("^", token) == 0
  );
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
