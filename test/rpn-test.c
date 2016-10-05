#include <stdlib.h>

#include <check.h>

#include "test/conversion-suite.h"
#include "test/error-handling-suite.h"

int main(void) {
  SRunner *srunner = srunner_create(conversion_suite());
  srunner_add_suite(srunner, error_handling_suite());

  srunner_run_all(srunner, CK_ENV);
  int ntests_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return (ntests_failed > 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
