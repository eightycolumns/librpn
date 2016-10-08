#ifndef RPN_H
#define RPN_H

enum {
  RPN_SUCCESS,
  RPN_MALFORMED_EXPRESSION_ERROR,
  RPN_MEMORY_ALLOCATION_ERROR,
  RPN_NULL_POINTER_ERROR
};

int infix_to_postfix(char *postfix, const char *infix);
int postfix_to_infix(char *infix, const char *postfix);

#endif
