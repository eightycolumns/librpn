#include "src/associativity.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

bool is_nonassociative(const char *operator) {
  assert(operator != NULL);
  return strcmp("-", operator) == 0 || strcmp("/", operator) == 0;
}

bool is_left_associative(const char *operator) {
  assert(operator != NULL);

  return (
    strcmp("+", operator) == 0 ||
    strcmp("-", operator) == 0 ||
    strcmp("*", operator) == 0 ||
    strcmp("/", operator) == 0
  );
}

bool is_right_associative(const char *operator) {
  assert(operator != NULL);
  return strcmp("^", operator) == 0;
}
