
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