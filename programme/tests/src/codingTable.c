
#include "codingTable.h"
#include <CUnit/Basic.h>

#define CODING_TABLE_MAXIMUM_SIZE 256

void test_coding_table_create(){
    CodingTable table = coding_table_create();
    CU_ASSERT_EQUAL(table.length,0);
}

void test_coding_table_add(){

}

void test_coding_table_get_value(){

}

void test_coding_table_is_present(){

}

void coding_table_add_tests()
{
    CU_pSuite suite = CU_add_suite("codingTable", NULL, NULL);
    CU_add_test(suite, "test_coding_table_create", test_coding_table_create);
    CU_add_test(suite, "test_coding_table_add", test_coding_table_add);
    CU_add_test(suite, "test_coding_table_get_value", test_coding_table_get_value);
    CU_add_test(suite, "test_coding_table_is_present", test_coding_table_is_present);
}