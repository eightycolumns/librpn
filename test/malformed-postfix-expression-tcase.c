#include "test/malformed-postfix-expression-tcase.h"

#include <check.h>

#include "src/rpn.h"

static void test_for_malformed_expression_error(const char *input) {
  int expected_error_code = RPN_MALFORMED_EXPRESSION_ERROR;
  char output[] = "";

  int actual_error_code = postfix_to_infix(output, input);

  ck_assert_msg(
    expected_error_code == actual_error_code,
    "Input \"%s\". Expected error code %d, got %d.",
    input, expected_error_code, actual_error_code
  );
}

START_TEST(test_01) {
  test_for_malformed_expression_error("+");
} END_TEST

TCase *malformed_postfix_expression_tcase(void) {
  TCase *malformed_postfix_expression_tcase = tcase_create(
    "Malformed Postfix Expression"
  );

  tcase_add_test(malformed_postfix_expression_tcase, test_01);

  return malformed_postfix_expression_tcase;
}
