#include "huffmanTree.h"
#include <CUnit/Basic.h>

void test_HuffmanTree_new_leaf()
{
    HuffmanTree *tree = HuffmanTree_new_leaf('a', 6);
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_EQUAL(HuffmanTree_get_value(tree), 'a');
    CU_ASSERT_EQUAL(HuffmanTree_get_weight(tree), 6);
    HuffmanTree_delete(tree);
}

void test_HuffmanTree_new_tree()
{
    HuffmanTree *left = HuffmanTree_new_leaf('a', 1);
    HuffmanTree *right = HuffmanTree_new_leaf('b', 2);
    HuffmanTree *tree = HuffmanTree_new_tree(left, right);
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_PTR_NOT_NULL(HuffmanTree_get_left_child(tree));
    CU_ASSERT_PTR_NOT_NULL(HuffmanTree_get_right_child(tree));
    CU_ASSERT_PTR_EQUAL(HuffmanTree_get_left_child(tree), left);
    CU_ASSERT_PTR_EQUAL(HuffmanTree_get_right_child(tree), right);
    HuffmanTree_delete(tree);
}

void test_HuffmanTree_is_leaf()
{
    HuffmanTree *left = HuffmanTree_new_leaf('a', 1);
    CU_ASSERT_TRUE(HuffmanTree_is_leaf(left));
    HuffmanTree *right = HuffmanTree_new_leaf('b', 2);
    CU_ASSERT_TRUE(HuffmanTree_is_leaf(right));
    HuffmanTree *tree = HuffmanTree_new_tree(left, right);
    CU_ASSERT_FALSE(HuffmanTree_is_leaf(tree));
    HuffmanTree_delete(tree);
}

void HuffmanTree_add_tests()
{
    CU_pSuite suite = CU_add_suite("HuffmanTree", NULL, NULL);
    CU_add_test(suite, "test_HuffmanTree_new_leaf", test_HuffmanTree_new_leaf);
    CU_add_test(suite, "test_HuffmanTree_new_tree", test_HuffmanTree_new_tree);
    CU_add_test(suite, "test_HuffmanTree_is_leaf", test_HuffmanTree_is_leaf);
}