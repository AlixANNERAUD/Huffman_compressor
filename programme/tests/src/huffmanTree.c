#include "huffmanTree.h"
#include "byte.h"
#include <CUnit/Basic.h>

void test_huffman_tree_new_leaf()
{
    HuffmanTree tree = huffman_tree_new_leaf(byte_create(15), 6);
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_EQUAL(byte_to_natural(huffman_tree_get_value(tree)), 15);
    CU_ASSERT_EQUAL(huffman_tree_get_weight(tree), 6);
    huffman_tree_delete(tree);
}

void test_huffman_tree_new_tree()
{
    HuffmanTree left = huffman_tree_new_leaf(byte_create(1), 1);
    HuffmanTree right = huffman_tree_new_leaf(byte_create(55), 2);
    HuffmanTree tree = huffman_tree_new_tree(left, right);
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_PTR_NOT_NULL(huffman_tree_get_left_child(tree));
    CU_ASSERT_PTR_NOT_NULL(huffman_tree_get_right_child(tree));
    CU_ASSERT_PTR_EQUAL(huffman_tree_get_left_child(tree), left);
    CU_ASSERT_PTR_EQUAL(huffman_tree_get_right_child(tree), right);
    huffman_tree_delete(tree);
}

void test_huffman_tree_is_leaf()
{
    HuffmanTree left = huffman_tree_new_leaf(byte_to_natural(1), 1);
    CU_ASSERT_TRUE(huffman_tree_is_leaf(left));
    HuffmanTree right = huffman_tree_new_leaf(byte_to_natural(2), 2);
    CU_ASSERT_TRUE(huffman_tree_is_leaf(right));
    HuffmanTree tree = huffman_tree_new_tree(left, right);
    CU_ASSERT_FALSE(huffman_tree_is_leaf(tree));
    huffman_tree_delete(tree);
}

void test_huffman_tree_greater_than()
{
    HuffmanTree left = huffman_tree_new_leaf(byte_to_natural(1), 1);
    HuffmanTree right = huffman_tree_new_leaf(byte_to_natural(2), 2);
    CU_ASSERT_TRUE(huffman_tree_greater_than(right, left));
    CU_ASSERT_FALSE(huffman_tree_greater_than(left, right));
    huffman_tree_delete(left);
    huffman_tree_delete(right);
}

void huffman_tree_add_tests()
{
    CU_pSuite suite = CU_add_suite("HuffmanTree", NULL, NULL);
    CU_add_test(suite, "test_huffman_tree_new_leaf", test_huffman_tree_new_leaf);
    CU_add_test(suite, "test_huffman_tree_new_tree", test_huffman_tree_new_tree);
    CU_add_test(suite, "test_huffman_tree_is_leaf", test_huffman_tree_is_leaf);
    CU_add_test(suite, "test_huffman_tree_greater_than", test_huffman_tree_greater_than);
}
