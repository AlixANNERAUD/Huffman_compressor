
#include "codingTable.h"
#include <CUnit/Basic.h>

#define CODING_TABLE_MAXIMUM_SIZE 256

void test_coding_table_create(){
    CodingTable table = coding_table_create();
    CU_ASSERT_EQUAL(table.length,0);
}

void test_coding_table_add(){
    CodingTable table = coding_table_create();

    BinaryCode bc = binary_code_create();
    binary_code_add_bit(&bc, BIT_0);

    coding_table_add(&table,'a',bc);
    CU_ASSERT_EQUAL(table.length,1);
    CU_ASSERT_EQUAL(table.entries[0].key,'a');
    CU_ASSERT_EQUAL(table.entries[0].value.bits[0],bc.bits[0]);

    binary_code_add_bit(&bc, BIT_1);

    coding_table_add(&table,'b',8);
    coding_table_add(&table,'c',7);
    CU_ASSERT_EQUAL(table.length,3);

    CU_ASSERT_EQUAL(table.entries[2].key,'c');
    CU_ASSERT_EQUAL(table.entries[1].value,8);
}

void test_coding_table_get_value(){
    CodingTable table = coding_table_create();
    coding_table_add(&table,'a',7);
    CU_ASSERT(coding_table_is_present(&table,'a'));
    coding_table_add(&table,'b',5);
    CU_ASSERT(coding_table_is_present(&table,'b'));
    CU_ASSERT(!coding_table_is_present(&table,'c'));
    CU_ASSERT_EQUAL(coding_table_get_value(&table,'a'),7);
    CU_ASSERT_EQUAL(coding_table_get_value(&table,'b'),5);
}

void test_coding_table_is_present(){
    CodingTable table = coding_table_create();
    coding_table_add(&table,'a',4);
    coding_table_add(&table,'b',8);
    coding_table_add(&table,'c',7);
    CU_ASSERT_TRUE(coding_table_is_present(&table,'a'));
    CU_ASSERT_TRUE(coding_table_is_present(&table,'b'));
    CU_ASSERT_TRUE(coding_table_is_present(&table,'c'));
}

void coding_table_add_tests()
{
    CU_pSuite suite = CU_add_suite("codingTable", NULL, NULL);
    CU_add_test(suite, "test_coding_table_create", test_coding_table_create);
    CU_add_test(suite, "test_coding_table_add", test_coding_table_add);
    CU_add_test(suite, "test_coding_table_get_value", test_coding_table_get_value);
    CU_add_test(suite, "test_coding_table_is_present", test_coding_table_is_present);
}
