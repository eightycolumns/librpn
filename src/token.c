#include "src/token.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

bool is_operand(const char *token) {
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

bool is_operator(const char *token) {
  assert(token != NULL);

  return (
    strcmp("+", token) == 0 ||
    strcmp("-", token) == 0 ||
    strcmp("*", token) == 0 ||
    strcmp("/", token) == 0 ||
    strcmp("^", token) == 0
  );
}
