#include "src/rpn.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "src/associativity.h"
#include "src/is-valid-infix.h"
#include "src/precedence.h"
#include "src/stack.h"
#include "src/token.h"
#include "src/util.h"

static bool stack_takes_precedence(const Stack *stack, const char *operator);

int infix_to_postfix(char *postfix, const char *infix) {
  if (postfix == NULL || infix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  if (!is_valid_infix(infix)) {
    return RPN_MALFORMED_EXPRESSION_ERROR;
  }

  strcpy(postfix, "");

  Stack *stack = NULL;

  size_t infix_length = strlen(infix);

  for (size_t i = 0; i < infix_length; i += 1) {
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

      if (push(&stack, token) == NULL) {
        clear(&stack);
        return RPN_MEMORY_ALLOCATION_ERROR;
      }
    } else if (is_opening_paren(token)) {
      if (push(&stack, token) == NULL) {
        clear(&stack);
        return RPN_MEMORY_ALLOCATION_ERROR;
      }
    } else if (is_closing_paren(token)) {
      while (!is_opening_paren(peek(stack))) {
        char operator[2];
        pop(operator, &stack);
        strcat(postfix, operator);
      }

      char opening_paren[2];
      pop(opening_paren, &stack);
    }
  }

  while (!is_empty(stack)) {
    char operator[2];
    pop(operator, &stack);
    strcat(postfix, operator);
  }

  return RPN_SUCCESS;
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
