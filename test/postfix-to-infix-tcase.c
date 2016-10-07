#include "test/postfix-to-infix-tcase.h"

#include <string.h>

#include <check.h>

#include "src/rpn.h"

START_TEST(test_01) {
  char input[] = "ab+c-";
  char expected_output[] = "a+b-c";
  char actual_output[strlen(expected_output) + 1];

  postfix_to_infix(actual_output, input);

  ck_assert_msg(
    strcmp(expected_output, actual_output) == 0,
    "Input \"%s\". Expected output \"%s\", got \"%s\".",
    input, expected_output, actual_output
  );
} END_TEST

START_TEST(test_02) {
  char input[] = "ab-c+";
  char expected_output[] = "a-b+c";
  char actual_output[strlen(expected_output) + 1];

  postfix_to_infix(actual_output, input);

  ck_assert_msg(
    strcmp(expected_output, actual_output) == 0,
    "Input \"%s\". Expected output \"%s\", got \"%s\".",
    input, expected_output, actual_output
  );
} END_TEST

TCase *postfix_to_infix_tcase(void) {
  TCase *postfix_to_infix_tcase = tcase_create("Postfix to Infix");

  tcase_add_test(postfix_to_infix_tcase, test_01);
  tcase_add_test(postfix_to_infix_tcase, test_02);

  return postfix_to_infix_tcase;
}
