#include "src/rpn.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "src/associativity.h"
#include "src/precedence.h"
#include "src/stack.h"
#include "src/token.h"
#include "src/util.h"

static bool stack_takes_precedence(const Stack *stack, const char *operator);

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

int postfix_to_infix(char *infix, const char *postfix) {
  if (infix == NULL || postfix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  Stack *stack = NULL;

  for (size_t i = 0; i < strlen(postfix); i += 1) {
    char token[2];
    copy_substring(token, postfix + i, 1);

    if (is_operand(token)) {
      if (push(&stack, token) == NULL) {
        clear(&stack);
        return RPN_MEMORY_ALLOCATION_ERROR;
      }
    } else if (is_operator(token)) {
      char r_operand[strlen(peek(stack)) + 1];
      pop(r_operand, &stack);

      char l_operand[strlen(peek(stack)) + 1];
      pop(l_operand, &stack);

      strcpy(infix, "");

      if (!is_operand(l_operand)) {
        int low = 0;

        int inside_parens = 0;

        for (size_t i = 0; i < strlen(l_operand); i += 1) {
          char token[2];
          copy_substring(token, l_operand + i, 1);

          if (is_opening_paren(token)) {
            inside_parens += 1;
          } else if (is_closing_paren(token)) {
            inside_parens -= 1;
          }

          if (inside_parens) {
            continue;
          }

          if (is_operator(token) && (low == 0 || precedence_of(token) < low)) {
            low = precedence_of(token);
          }
        }

        if (low < precedence_of(token)) {
          strcat(infix, "(");
          strcat(infix, l_operand);
          strcat(infix, ")");
        } else {
          strcat(infix, l_operand);
        }
      } else {
        strcat(infix, l_operand);
      }

      strcat(infix, token);

      if (!is_operand(r_operand)) {
        int low = 0;

        int inside_parens = 0;

        for (size_t i = 0; i < strlen(r_operand); i += 1) {
          char token[2];
          copy_substring(token, r_operand + i, 1);

          if (is_opening_paren(token)) {
            inside_parens += 1;
          } else if (is_closing_paren(token)) {
            inside_parens -= 1;
          }

          if (inside_parens) {
            continue;
          }

          if (is_operator(token) && (low == 0 || precedence_of(token) < low)) {
            low = precedence_of(token);
          }
        }

        if (low < precedence_of(token)) {
          strcat(infix, "(");
          strcat(infix, r_operand);
          strcat(infix, ")");
        } else {
          strcat(infix, r_operand);
        }
      } else {
        strcat(infix, r_operand);
      }

      if (push(&stack, infix) == NULL) {
        clear(&stack);
        return RPN_MEMORY_ALLOCATION_ERROR;
      }
    }
  }

  clear(&stack);

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
