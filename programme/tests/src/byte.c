#include "byte.h"
#include <CUnit/Basic.h>

void test_byte_create(){

}

void test_byte_to_natural(){

}

void test_byte_set_bit(){

}

void test_byte_get_bit(){

}

void byte_add_tests()
{
    CU_pSuite suite = CU_add_suite("byte", NULL, NULL);
    CU_add_test(suite, "test_byte_create", test_byte_create);
    CU_add_test(suite, "test_byte_to_natural", test_byte_to_natural);
    CU_add_test(suite, "test_byte_set_bit", test_byte_set_bit);
    CU_add_test(suite, "test_byte_get_bit", test_byte_get_bit);
}