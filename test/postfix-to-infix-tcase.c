#include "test/postfix-to-infix-tcase.h"

#include <string.h>

#include <check.h>

#include "src/rpn.h"

static void test_postfix_to_infix(
  const char *expected_output,
  const char *input
) {
  char actual_output[strlen(expected_output) + 1];

  postfix_to_infix(actual_output, input);

  ck_assert_msg(
    strcmp(expected_output, actual_output) == 0,
    "Input \"%s\". Expected output \"%s\", got \"%s\".",
    input, expected_output, actual_output
  );
}

START_TEST(test_01) {
  test_postfix_to_infix("a+b-c", "ab+c-");
} END_TEST

START_TEST(test_02) {
  test_postfix_to_infix("a-b+c", "ab-c+");
} END_TEST

START_TEST(test_03) {
  test_postfix_to_infix("a*b/c", "ab*c/");
} END_TEST

START_TEST(test_04) {
  test_postfix_to_infix("a/b*c", "ab/c*");
} END_TEST

START_TEST(test_05) {
  test_postfix_to_infix("a+b*c", "abc*+");
} END_TEST

START_TEST(test_06) {
  test_postfix_to_infix("a^b^c", "abc^^");
} END_TEST

START_TEST(test_07) {
  test_postfix_to_infix("a+b-c*d/e^f", "ab+cd*ef^/-");
} END_TEST

START_TEST(test_08) {
  test_postfix_to_infix("a^b*c/d+e-f", "ab^c*d/e+f-");
} END_TEST

START_TEST(test_09) {
  test_postfix_to_infix("a+b*c^d*e+f", "abcd^*e*+f+");
} END_TEST

START_TEST(test_10) {
  test_postfix_to_infix("(a+b-c)*d/e^f", "ab+c-d*ef^/");
} END_TEST

START_TEST(test_11) {
  test_postfix_to_infix("((a+b-c)*d/e)^f", "ab+c-d*e/f^");
} END_TEST

TCase *postfix_to_infix_tcase(void) {
  TCase *postfix_to_infix_tcase = tcase_create("Postfix to Infix");

  tcase_add_test(postfix_to_infix_tcase, test_01);
  tcase_add_test(postfix_to_infix_tcase, test_02);
  tcase_add_test(postfix_to_infix_tcase, test_03);
  tcase_add_test(postfix_to_infix_tcase, test_04);
  tcase_add_test(postfix_to_infix_tcase, test_05);
  tcase_add_test(postfix_to_infix_tcase, test_06);
  tcase_add_test(postfix_to_infix_tcase, test_07);
  tcase_add_test(postfix_to_infix_tcase, test_08);
  tcase_add_test(postfix_to_infix_tcase, test_09);
  tcase_add_test(postfix_to_infix_tcase, test_10);
  tcase_add_test(postfix_to_infix_tcase, test_11);

  return postfix_to_infix_tcase;
}
