#include "test/infix-to-postfix-tcase.h"

#include <string.h>

#include <check.h>

#include "src/rpn.h"

START_TEST(test_01) {
  char input[] = "a+b-c";
  char expected_output[] = "ab+c-";
  char actual_output[strlen(expected_output) + 1];

  infix_to_postfix(actual_output, input);

  ck_assert_msg(
    strcmp(expected_output, actual_output) == 0,
    "Input \"%s\". Expected output \"%s\", got \"%s\".",
    input, expected_output, actual_output
  );
} END_TEST

START_TEST(test_02) {
  char input[] = "a-b+c";
  char expected_output[] = "ab-c+";
  char actual_output[strlen(expected_output) + 1];

  infix_to_postfix(actual_output, input);

  ck_assert_msg(
    strcmp(expected_output, actual_output) == 0,
    "Input \"%s\". Expected output \"%s\", got \"%s\".",
    input, expected_output, actual_output
  );
} END_TEST

TCase *infix_to_postfix_tcase(void) {
  TCase *infix_to_postfix_tcase = tcase_create("Infix to Postfix");

  tcase_add_test(infix_to_postfix_tcase, test_01);
  tcase_add_test(infix_to_postfix_tcase, test_02);

  return infix_to_postfix_tcase;
}
