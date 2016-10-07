#include "test/infix-to-postfix-tcase.h"

#include <string.h>

#include <check.h>

#include "src/rpn.h"

static void test_infix_to_postfix(
  const char *expected_output,
  const char *input
) {
  char actual_output[strlen(expected_output) + 1];

  infix_to_postfix(actual_output, input);

  ck_assert_msg(
    strcmp(expected_output, actual_output) == 0,
    "Input \"%s\". Expected output \"%s\", got \"%s\".",
    input, expected_output, actual_output
  );
}

START_TEST(test_01) {
  test_infix_to_postfix("ab+c-", "a+b-c");
} END_TEST

START_TEST(test_02) {
  test_infix_to_postfix("ab-c+", "a-b+c");
} END_TEST

START_TEST(test_03) {
  test_infix_to_postfix("ab*c/", "a*b/c");
} END_TEST

TCase *infix_to_postfix_tcase(void) {
  TCase *infix_to_postfix_tcase = tcase_create("Infix to Postfix");

  tcase_add_test(infix_to_postfix_tcase, test_01);
  tcase_add_test(infix_to_postfix_tcase, test_02);
  tcase_add_test(infix_to_postfix_tcase, test_03);

  return infix_to_postfix_tcase;
}
