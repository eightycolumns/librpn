#include "test/error-handling-suite.h"

#include <check.h>

Suite *error_handling_suite(void) {
  Suite *error_handling_suite = suite_create("Error Handling");
  return error_handling_suite;
}
