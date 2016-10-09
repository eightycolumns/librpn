#include "test/error-handling-suite.h"

#include <check.h>

#include "test/malformed-infix-expression-tcase.h"
#include "test/malformed-postfix-expression-tcase.h"
#include "test/null-pointer-error-tcase.h"

Suite *error_handling_suite(void) {
  Suite *error_handling_suite = suite_create("Error Handling");

  suite_add_tcase(error_handling_suite, malformed_infix_expression_tcase());
  suite_add_tcase(error_handling_suite, malformed_postfix_expression_tcase());
  suite_add_tcase(error_handling_suite, null_pointer_error_tcase());

  return error_handling_suite;
}
