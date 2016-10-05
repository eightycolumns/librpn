#include "src/rpn.h"

#include <stddef.h>

int infix_to_postfix(char *postfix, const char *infix) {
  (void)infix; // Suppress "unused parameter" warning

  if (postfix == NULL) {
    return RPN_NULL_POINTER_ERROR;
  }

  return RPN_SUCCESS;
}
