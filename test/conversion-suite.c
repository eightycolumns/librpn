#include "test/conversion-suite.h"

#include <check.h>

#include "test/infix-to-postfix-tcase.h"
#include "test/postfix-to-infix-tcase.h"

Suite *conversion_suite(void) {
  Suite *conversion_suite = suite_create("Conversion");

  suite_add_tcase(conversion_suite, infix_to_postfix_tcase());
  suite_add_tcase(conversion_suite, postfix_to_infix_tcase());

  return conversion_suite;
}
