#include "statistics.h"

#include "main.h"

#include "CUnit/Basic.h"

void test_statistics_statistics() {
    Statistics s = statistics_create();
}

void statistics_add_tests()
{
    CU_pSuite suite = CU_add_suite("statistics", NULL, NULL);
    CU_add_test(suite, "test_statistics_statistics", test_statistics_statistics);
}