
#include "codingTable.h"
#include <CUnit/Basic.h>

#define CODING_TABLE_MAXIMUM_SIZE 256

void test_coding_table_create()
{
    CodingTable table = coding_table_create();
    CU_ASSERT_EQUAL(table.length, 0);
}

void test_coding_table_add()
{
    CodingTable table = coding_table_create();

    BinaryCode bc = binary_code_create();
    binary_code_add_bit(&bc, BIT_0);

    coding_table_add(&table, byte_create('a'), bc);
    CU_ASSERT_EQUAL(table.length, 1);
    CU_ASSERT_EQUAL(table.entries[0].key, byte_create('a'));
    CU_ASSERT_EQUAL(table.entries[0].value.bits[0], bc.bits[0]);

    binary_code_add_bit(&bc, BIT_1);

    coding_table_add(&table, byte_create('b'), binary_code_create());
    coding_table_add(&table, byte_create('c'), binary_code_create());
    CU_ASSERT_EQUAL(table.length, 3);

    CU_ASSERT_EQUAL(table.entries[2].key, byte_create('c'));
}

void test_coding_table_get_value()
{
    CodingTable table = coding_table_create();
    coding_table_add(&table, byte_create('a'), binary_code_create());
    CU_ASSERT(coding_table_search(&table, byte_create('a'), NULL));
    coding_table_add(&table, byte_create('b'), binary_code_create());
    CU_ASSERT(coding_table_search(&table, byte_create('b'), NULL));
    CU_ASSERT(!coding_table_search(&table, byte_create('c'), NULL));
}

void test_coding_table_search()
{
    CodingTable table = coding_table_create();
    coding_table_add(&table, byte_create('a'), binary_code_create());
    coding_table_add(&table, byte_create('b'), binary_code_create());
    coding_table_add(&table, byte_create('c'), binary_code_create());
    size_t index;
    CU_ASSERT(coding_table_search(&table, byte_create('a'), &index));
    CU_ASSERT_EQUAL(index, 0);
    CU_ASSERT(coding_table_search(&table, byte_create('b'), NULL));
    CU_ASSERT(coding_table_search(&table, byte_create('c'), &index));
    CU_ASSERT_EQUAL(index, 2);
    CU_ASSERT(!coding_table_search(&table, byte_create('d'), NULL));
}

void coding_table_add_tests()
{
    CU_pSuite suite = CU_add_suite("codingTable", NULL, NULL);
    CU_add_test(suite, "test_coding_table_create", test_coding_table_create);
    CU_add_test(suite, "test_coding_table_add", test_coding_table_add);
    CU_add_test(suite, "test_coding_table_get_value", test_coding_table_get_value);
    CU_add_test(suite, "test_coding_table_is_present", test_coding_table_search);
}
