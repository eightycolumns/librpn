#include "src/infix-validation.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "src/token.h"
#include "src/util.h"

static bool is_parenthesized_subexpression(const char *infix, size_t i);
static size_t find_closing_paren(const char *infix, size_t i);
static bool is_valid_token(const char *infix, size_t i);
static bool is_valid_operand_placement(const char *infix, size_t i);
static bool is_valid_operator_placement(const char *infix, size_t i);

bool is_valid_infix_expression(const char *infix) {
  assert(infix != NULL);

  if (is_empty_string(infix) || is_entirely_whitespace(infix)) {
    return false;
  }

  for (size_t i = 0; i < strlen(infix); i += 1) {
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

  size_t substr_length = substr_stop - substr_start;

  char infix_substr[substr_length + 1];
  copy_substring(infix_substr, infix + substr_start, substr_length);

  return is_valid_infix_expression(infix_substr);
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

  if (is_whitespace(token)) {
    return true;
  }

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
