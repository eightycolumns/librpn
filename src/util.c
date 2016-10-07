#include "src/util.h"

#include <assert.h>
#include <string.h>

char *copy_substring(char *dest, const char *src, size_t n) {
  assert(dest != NULL);
  assert(src != NULL);
  assert(n <= strlen(src));

  strncpy(dest, src, n);
  dest[n] = '\0';

  return dest;
}
