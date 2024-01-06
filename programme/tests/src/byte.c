#include "byte.h"
#include <CUnit/Basic.h>

void test_byte_create()
{
    for (unsigned int i = 0; i < 256; i++)
    {
        Byte b = byte_create(i);
        CU_ASSERT_EQUAL(b, i);
    }
}

void test_byte_to_natural()
{
    Byte b = byte_create(122);
    CU_ASSERT_EQUAL(b, 122);
}

void test_byte_set_bit()
{
    Byte b = byte_create(128);
    byte_set_bit(&b, 7, BIT_0);
    CU_ASSERT_EQUAL(b, 0);
    byte_set_bit(&b, 0, BIT_1);
    CU_ASSERT_EQUAL(b, 1);
}

void test_byte_get_bit()
{
    Byte b = byte_create(128);
    Bit b0 = byte_get_bit(b, 7);
    CU_ASSERT_EQUAL(b0, BIT_1);
}

void test_byte_set_and_get_bit()
{
    for (unsigned int i = 0; i < 8; i++)
    {
        Byte b = byte_create(0);
        byte_set_bit(&b, i, BIT_0);
        CU_ASSERT_EQUAL(byte_get_bit(b, i), BIT_0);
        byte_set_bit(&b, i, BIT_1);
        for (unsigned int j = 0; j < i; j++)
        {
            if (j == i)
                CU_ASSERT_EQUAL(byte_get_bit(b, j), BIT_1)
            else
                CU_ASSERT_EQUAL(byte_get_bit(b, j), BIT_0);
        }
    }

    for (unsigned int i = 0; i < 8; i++)
    {
        Byte b = byte_create(255);
        byte_set_bit(&b, i, BIT_1);
        CU_ASSERT_EQUAL(byte_get_bit(b, i), BIT_1);
        byte_set_bit(&b, i, BIT_0);
        for (unsigned int j = 0; j < i; j++)
        {
            if (j == i)
                CU_ASSERT_EQUAL(byte_get_bit(b, j), BIT_0)
            else
                CU_ASSERT_EQUAL(byte_get_bit(b, j), BIT_1);
        }
    }
}

void byte_add_tests()
{
    CU_pSuite suite = CU_add_suite("byte", NULL, NULL);
    CU_add_test(suite, "test_byte_create", test_byte_create);
    CU_add_test(suite, "test_byte_to_natural", test_byte_to_natural);
    CU_add_test(suite, "test_byte_set_bit", test_byte_set_bit);
    CU_add_test(suite, "test_byte_get_bit", test_byte_get_bit);
    CU_add_test(suite, "test_byte_set_and_get_bit", test_byte_set_and_get_bit);
}
