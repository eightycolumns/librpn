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

START_TEST(test_04) {
  test_infix_to_postfix("ab/c*", "a/b*c");
} END_TEST

START_TEST(test_05) {
  test_infix_to_postfix("abc*+", "a+b*c");
} END_TEST

START_TEST(test_06) {
  test_infix_to_postfix("abc^^", "a^b^c");
} END_TEST

START_TEST(test_07) {
  test_infix_to_postfix("ab+cd*ef^/-", "a+b-c*d/e^f");
} END_TEST

START_TEST(test_08) {
  test_infix_to_postfix("ab^c*d/e+f-", "a^b*c/d+e-f");
} END_TEST

START_TEST(test_09) {
  test_infix_to_postfix("abcd^*e*+f+", "a+b*c^d*e+f");
} END_TEST

START_TEST(test_10) {
  test_infix_to_postfix("ab+c-d*ef^/", "(a+b-c)*d/e^f");
} END_TEST

START_TEST(test_11) {
  test_infix_to_postfix("ab+c-d*e/f^", "((a+b-c)*d/e)^f");
} END_TEST

START_TEST(test_12) {
  test_infix_to_postfix("ab+c*def+*^", "((a+b)*c)^(d*(e+f))");
} END_TEST

START_TEST(test_13) {
  test_infix_to_postfix("ab+cd+ef+^^", "(a+b)^(c+d)^(e+f)");
} END_TEST

START_TEST(test_14) {
  test_infix_to_postfix("abc^+d*", "(a+b^c)*d");
} END_TEST

START_TEST(test_15) {
  test_infix_to_postfix("abc^d+*", "a*(b^c+d)");
} END_TEST

TCase *infix_to_postfix_tcase(void) {
  TCase *infix_to_postfix_tcase = tcase_create("Infix to Postfix");

  tcase_add_test(infix_to_postfix_tcase, test_01);
  tcase_add_test(infix_to_postfix_tcase, test_02);
  tcase_add_test(infix_to_postfix_tcase, test_03);
  tcase_add_test(infix_to_postfix_tcase, test_04);
  tcase_add_test(infix_to_postfix_tcase, test_05);
  tcase_add_test(infix_to_postfix_tcase, test_06);
  tcase_add_test(infix_to_postfix_tcase, test_07);
  tcase_add_test(infix_to_postfix_tcase, test_08);
  tcase_add_test(infix_to_postfix_tcase, test_09);
  tcase_add_test(infix_to_postfix_tcase, test_10);
  tcase_add_test(infix_to_postfix_tcase, test_11);
  tcase_add_test(infix_to_postfix_tcase, test_12);
  tcase_add_test(infix_to_postfix_tcase, test_13);
  tcase_add_test(infix_to_postfix_tcase, test_14);
  tcase_add_test(infix_to_postfix_tcase, test_15);

  return infix_to_postfix_tcase;
}
