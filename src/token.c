#include "src/token.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool is_operand(const char *token) {
  assert(token != NULL);
  return strlen(token) == 1 && islower(token[0]);
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

bool is_opening_paren(const char *token) {
  assert(token != NULL);
  return strcmp("(", token) == 0;
}
