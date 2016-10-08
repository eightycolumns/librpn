#include "src/precedence.h"

#include <assert.h>
#include <string.h>

#include "src/token.h"
#include "src/util.h"

int precedence_of(const char *operator) {
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

int lowest_operator_precedence_in(const char *expression) {
  assert(expression != NULL);

  int low = 0;

  int inside_parens = 0;

  for (size_t i = 0; i < strlen(expression); i += 1) {
    char token[2];
    copy_substring(token, expression + i, 1);

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

  return low;
}
