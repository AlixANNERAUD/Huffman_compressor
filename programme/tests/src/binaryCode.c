/**
 * @file binaryCode.c
 * fichier de test du TAD Code Binaire
*/

#include "binaryCode.h"
#include <CUnit/Basic.h>

/**
 * @fn void test_binary_code_create()
 * @brief Fonction qui test binary_code_create
*/
void test_binary_code_create() {
    BinaryCode code = binary_code_create();
    CU_ASSERT_EQUAL(code.length,0);
}

/**
 * @fn void test_binary_code_get_length() 
 * @brief Fonction qui test binary_code_get_length
*/
void test_binary_code_get_length() {
    BinaryCode code = binary_code_create();
    CU_ASSERT_EQUAL(binary_code_get_length(&code),0);
}

/**
 * @fn void test_binary_code_get_bit()
 * @brief Fonction qui test binary_code_get_bit
*/
void test_binary_code_get_bit() {
    BinaryCode code = binary_code_create();
    code.length = code.length+1;
    code.bits[0] = BIT_0;
    CU_ASSERT_EQUAL(binary_code_get_bit(&code,0),BIT_0);
}

/**
 * @fn void test_binary_code_add_bit()
 * @brief Fonction qui test binary_code_add_bit
*/
void test_binary_code_add_bit() {
    BinaryCode code = binary_code_create();
    binary_code_add_bit(&code,BIT_1);
    CU_ASSERT_EQUAL(code.bits[code.length-1],BIT_1);
}

/**
 * @fn void test_binary_code_remove_bit()
 * @brief Fonction qui test void binary_code_remove_bit
*/
void test_binary_code_remove_bit() {
    BinaryCode code = binary_code_create();
    code.length=code.length+2;
    code.bits[0]=BIT_0;
    code.bits[1]=BIT_1;
    binary_code_remove_bit(&code,0);
    CU_ASSERT_EQUAL(code.length,1);
    CU_ASSERT_EQUAL(code.bits[code.length-1],BIT_1);
}

/**
 * @fn void test_binary_code_remove_last_bit()
 * @brief Fonction qui test void binary_code_remove_last_bit
*/
void test_binary_code_remove_last_bit() {
    BinaryCode code = binary_code_create();
    code.length=code.length+2;
    code.bits[0]=BIT_0;
    code.bits[1]=BIT_1;
    binary_code_remove_last_bit(&code);
    CU_ASSERT_EQUAL(code.bits[code.length-1],BIT_0);
}

/**
 * @fn void binary_code_add_tests()
 * @brief fonction qui ajoute tout les tests du TAD code bianire pour les tester
*/
void binary_code_add_tests()
{
    CU_pSuite suite = CU_add_suite("binaryCode", NULL, NULL);
    CU_add_test(suite, "test_binary_code_create", test_binary_code_create);
    CU_add_test(suite, "test_binary_code_get_length", test_binary_code_get_length);
    CU_add_test(suite, "test_binary_code_get_bit", test_binary_code_get_bit);
    CU_add_test(suite, "test_binary_code_add_bit", test_binary_code_add_bit);
    CU_add_test(suite, "test_binary_code_remove_bit", test_binary_code_remove_bit);
    CU_add_test(suite, "test_binary_code_remove_last_bit", test_binary_code_remove_last_bit);
}
