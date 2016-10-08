#ifndef ASSOCIATIVITY_H
#define ASSOCIATIVITY_H

#include <stdbool.h>

bool is_nonassociative(const char *operator);
bool is_left_associative(const char *operator);
bool is_right_associative(const char *operator);

#endif
