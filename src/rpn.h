#ifndef RPN_H
#define RPN_H

enum {
  RPN_SUCCESS,
  RPN_NULL_POINTER_ERROR
};

int infix_to_postfix(char *postfix, const char *infix);

#endif
