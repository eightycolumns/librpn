#include "src/precedence.h"

#include <assert.h>
#include <string.h>

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
