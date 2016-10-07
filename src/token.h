#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

bool is_operand(const char *token);
bool is_operator(const char *token);
bool is_opening_paren(const char *token);
bool is_closing_paren(const char *token);

#endif
