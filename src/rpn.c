#include "src/rpn.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "src/associativity.h"
#include "src/infix-validation.h"
#include "src/precedence.h"
#include "src/stack.h"
#include "src/token.h"
#include "src/util.h"

static bool stack_takes_precedence(const Stack *stack, const char *operator);
static bool l_operand_needs_parens(const char *operand, const char *operator);
static bool r_operand_needs_parens(const char *operand, const char *operator);
static bool is_expression(const char *operand);
static char *parenthesize(char *dest, const char *src);
static bool is_valid_postfix_expression(const char *postfix);

int infix_to_postfix(char *postfix, const char *infix) {
  if (postfix == NULL || infix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  if (!is_valid_infix_expression(infix)) {
    return RPN_MALFORMED_EXPRESSION_ERROR;
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

  if (!is_valid_postfix_expression(postfix)) {
    return RPN_MALFORMED_EXPRESSION_ERROR;
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

      size_t room_for_parens = 2;

      if (l_operand_needs_parens(l_operand, token)) {
        char l_operand_parenthesized[strlen(l_operand) + room_for_parens + 1];
        parenthesize(l_operand_parenthesized, l_operand);
        strcat(infix, l_operand_parenthesized);
      } else {
        strcat(infix, l_operand);
      }

      strcat(infix, token);

      if (r_operand_needs_parens(r_operand, token)) {
        char r_operand_parenthesized[strlen(r_operand) + room_for_parens + 1];
        parenthesize(r_operand_parenthesized, r_operand);
        strcat(infix, r_operand_parenthesized);
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

static bool l_operand_needs_parens(const char *operand, const char *operator) {
  assert(operand != NULL);
  assert(operator != NULL);

  if (is_expression(operand) && is_left_associative(operator)) {
    return lowest_operator_precedence_in(operand) < precedence_of(operator);
  }

  if (is_expression(operand) && is_right_associative(operator)) {
    return lowest_operator_precedence_in(operand) <= precedence_of(operator);
  }

  return false;
}

static bool r_operand_needs_parens(const char *operand, const char *operator) {
  assert(operand != NULL);
  assert(operator != NULL);

  if (is_expression(operand) && is_left_associative(operator)) {
    if (is_associative(operator)) {
      return lowest_operator_precedence_in(operand) < precedence_of(operator);
    } else {
      return lowest_operator_precedence_in(operand) <= precedence_of(operator);
    }
  }

  if (is_expression(operand) && is_right_associative(operator)) {
    return lowest_operator_precedence_in(operand) < precedence_of(operator);
  }

  return false;
}

static bool is_expression(const char *operand) {
  assert(operand != NULL);
  return !is_operand(operand);
}

static char *parenthesize(char *dest, const char *src) {
  assert(dest != NULL);
  assert(src != NULL);

  strcpy(dest, "");

  strcat(dest, "(");
  strcat(dest, src);
  strcat(dest, ")");

  return dest;
}

static bool is_valid_postfix_expression(const char *postfix) {
  assert(postfix != NULL);

  int n_operands = 0;
  int n_operators = 0;

  for (size_t i = 0; i < strlen(postfix); i += 1) {
    char token[2];
    copy_substring(token, postfix + i, 1);

    if (is_operand(token)) {
      n_operands += 1;
    } else if (is_operator(token)) {
      n_operators += 1;
    } else {
      return false;
    }

    if (n_operands <= n_operators) {
      return false;
    }
  }

  return n_operands - 1 == n_operators;
}
