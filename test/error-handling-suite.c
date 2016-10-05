#include "test/error-handling-suite.h"

#include <check.h>

#include "test/null-pointer-error-tcase.h"

Suite *error_handling_suite(void) {
  Suite *error_handling_suite = suite_create("Error Handling");

  suite_add_tcase(error_handling_suite, null_pointer_error_tcase());

  return error_handling_suite;
}
