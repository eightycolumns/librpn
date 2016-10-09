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
static bool l_operand_needs_parens(const char *operand, const char *operator);
static bool r_operand_needs_parens(const char *operand, const char *operator);
static bool is_expression(const char *operand);
static char *parenthesize(char *dest, const char *src);
static bool is_valid_infix_expression(const char *infix);
static bool is_parenthesized_subexpression(const char *infix, size_t i);
static size_t find_closing_paren(const char *infix, size_t i);
static bool is_valid_token(const char *infix, size_t i);
static bool is_valid_operand_placement(const char *infix, size_t i);
static bool is_valid_operator_placement(const char *infix, size_t i);

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

static bool is_valid_infix_expression(const char *infix) {
  assert(infix != NULL);

  for (size_t i = 0; i < strlen(infix); i += 1) {
    char token[2];
    copy_substring(token, infix + i, 1);

    if (is_parenthesized_subexpression(infix, i)) {
      i = find_closing_paren(infix, i);
    } else if (!is_valid_token(infix, i)) {
      return false;
    }
  }

  return true;
}

static bool is_parenthesized_subexpression(const char *infix, size_t i) {
  assert(infix != NULL);
  assert(i < strlen(infix));

  char token[2];
  copy_substring(token, infix + i, 1);

  if (!is_opening_paren(token)) {
    return false;
  }

  size_t substr_start = i + 1;
  size_t substr_stop = find_closing_paren(infix, i);

  if (substr_stop < substr_start) {
    return false;
  }

  return true;
}

static size_t find_closing_paren(const char *infix, size_t i) {
  assert(infix != NULL);
  assert(i < strlen(infix));

  int n_parens = 0;

  for (size_t j = i; j < strlen(infix); j += 1) {
    char token[2];
    copy_substring(token, infix + j, 1);

    if (is_opening_paren(token)) {
      n_parens += 1;
    } else if (is_closing_paren(token)) {
      n_parens -= 1;
    }

    if (n_parens == 0) {
      return j;
    }
  }

  return i;
}

static bool is_valid_token(const char *infix, size_t i) {
  assert(infix != NULL);
  assert(i < strlen(infix));

  char token[2];
  copy_substring(token, infix + i, 1);

  if (is_operand(token) && is_valid_operand_placement(infix, i)) {
    return true;
  }

  if (is_operator(token) && is_valid_operator_placement(infix, i)) {
    return true;
  }

  return false;
}

static bool is_valid_operand_placement(const char *infix, size_t i) {
  assert(infix != NULL);
  assert(i < strlen(infix));

  if (i > 0) {
    char prev_token[2];
    copy_substring(prev_token, infix + i - 1, 1);

    if (is_operand(prev_token) || is_closing_paren(prev_token)) {
      return false;
    }
  }

  if (i < strlen(infix) - 1) {
    char next_token[2];
    copy_substring(next_token, infix + i + 1, 1);

    if (is_opening_paren(next_token)) {
      return false;
    }
  }

  return true;
}

static bool is_valid_operator_placement(const char *infix, size_t i) {
  assert(infix != NULL);
  assert(i < strlen(infix));

  if (i > 0 && i < strlen(infix) - 1) {
    char prev_token[2];
    copy_substring(prev_token, infix + i - 1, 1);

    if (is_operator(prev_token)) {
      return false;
    }
  } else {
    return false;
  }

  return true;
}
