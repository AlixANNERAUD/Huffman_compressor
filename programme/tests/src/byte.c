#include "byte.h"
#include <CUnit/Basic.h>

void test_byte_create(){
    Byte b = byte_create(122);
    CU_ASSERT_EQUAL(b,"122");
}

void test_byte_to_natural(){
    Byte b = byte_create(122);
    CU_ASSERT_EQUAL(b,122);
}

void test_byte_set_bit(){
    Byte b = byte_create(128);
    byte_set_bit(&b,0,BIT_0);
    CU_ASSERT_EQUAL(b,"0");
}

void test_byte_get_bit(){
    Byte b = byte_create(128);
    Bit b0 = byte_get_bit(b,0);
    CU_ASSERT_EQUAL(b0,BIT_1);
}

void byte_add_tests()
{
    CU_pSuite suite = CU_add_suite("byte", NULL, NULL);
    CU_add_test(suite, "test_byte_create", test_byte_create);
    CU_add_test(suite, "test_byte_to_natural", test_byte_to_natural);
    CU_add_test(suite, "test_byte_set_bit", test_byte_set_bit);
    CU_add_test(suite, "test_byte_get_bit", test_byte_get_bit);
} 