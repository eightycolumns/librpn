#include "src/is-valid-postfix.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "src/token.h"
#include "src/util.h"

bool is_valid_postfix(const char *postfix) {
  assert(postfix != NULL);

  if (is_empty_string(postfix) || is_entirely_whitespace(postfix)) {
    return false;
  }

  int n_operands = 0;
  int n_operators = 0;

  size_t postfix_length = strlen(postfix);

  for (size_t i = 0; i < postfix_length; i += 1) {
    char token[2];
    copy_substring(token, postfix + i, 1);

    if (is_whitespace(token)) {
      continue;
    } else if (is_operand(token)) {
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
