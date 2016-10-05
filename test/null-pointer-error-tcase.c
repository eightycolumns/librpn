#include "test/null-pointer-error-tcase.h"

#include <check.h>

#include "src/rpn.h"

START_TEST(postfix_dest_cannot_be_NULL) {
  int expected = RPN_NULL_POINTER_ERROR;
  int actual = infix_to_postfix(NULL, "");
  ck_assert_int_eq(expected, actual);
} END_TEST

TCase *null_pointer_error_tcase(void) {
  TCase *null_pointer_error_tcase = tcase_create("Null Pointer Error");

  tcase_add_test(null_pointer_error_tcase, postfix_dest_cannot_be_NULL);

  return null_pointer_error_tcase;
}
