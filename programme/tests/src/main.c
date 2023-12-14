#include "stdio.h"
#include "CUnit/Basic.h"

#include "main.h"
#include "common.h"

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add tests to suite
    pSuite = CU_add_suite("Suite_1", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // - Run all tests
    CU_basic_set_mode(CU_BRM_VERBOSE); // Set verbs mode
    CU_basic_run_tests();           // Run all tests
    CU_cleanup_registry();        // Clean registry
}