#include "test/null-pointer-error-tcase.h"

#include <check.h>

#include "src/rpn.h"

static char infix[] = "";
static char postfix[] = "";

START_TEST(postfix_dest_cannot_be_NULL) {
  int expected = RPN_NULL_POINTER_ERROR;
  int actual = infix_to_postfix(NULL, infix);
  ck_assert_int_eq(expected, actual);
} END_TEST

START_TEST(infix_src_cannot_be_NULL) {
  int expected = RPN_NULL_POINTER_ERROR;
  int actual = infix_to_postfix(postfix, NULL);
  ck_assert_int_eq(expected, actual);
} END_TEST

START_TEST(infix_dest_cannot_be_NULL) {
  int expected = RPN_NULL_POINTER_ERROR;
  int actual = postfix_to_infix(NULL, postfix);
  ck_assert_int_eq(expected, actual);
} END_TEST

START_TEST(postfix_src_cannot_be_NULL) {
  int expected = RPN_NULL_POINTER_ERROR;
  int actual = postfix_to_infix(infix, NULL);
  ck_assert_int_eq(expected, actual);
} END_TEST

TCase *null_pointer_error_tcase(void) {
  TCase *null_pointer_error_tcase = tcase_create("Null Pointer Error");

  tcase_add_test(null_pointer_error_tcase, postfix_dest_cannot_be_NULL);
  tcase_add_test(null_pointer_error_tcase, infix_src_cannot_be_NULL);
  tcase_add_test(null_pointer_error_tcase, infix_dest_cannot_be_NULL);
  tcase_add_test(null_pointer_error_tcase, postfix_src_cannot_be_NULL);

  return null_pointer_error_tcase;
}
