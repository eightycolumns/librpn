#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stddef.h>

char *copy_substring(char *dest, const char *src, size_t n);
bool is_empty_string(const char *string);
bool is_entirely_whitespace(const char *string);

#endif
