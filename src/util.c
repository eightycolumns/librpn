#include "src/util.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char *copy_substring(char *dest, const char *src, size_t n) {
  assert(dest != NULL);
  assert(src != NULL);
  assert(n <= strlen(src));

  strncpy(dest, src, n);
  dest[n] = '\0';

  return dest;
}

bool is_empty_string(const char *string) {
  assert(string != NULL);
  return strcmp("", string) == 0;
}

bool is_entirely_whitespace(const char *string) {
  assert(string != NULL);

  if (is_empty_string(string)) {
    return false;
  }

  size_t string_length = strlen(string);

  for (size_t i = 0; i < string_length; i += 1) {
    if (!isspace(string[i])) {
      return false;
    }
  }

  return true;
}
