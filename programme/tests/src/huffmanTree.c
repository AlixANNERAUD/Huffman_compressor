#include "huffmanTree.h"
#include <CUnit/Basic.h>

void test_huffman_tree_new_leaf()
{
    HuffmanTree tree = huffman_tree_new_leaf('a', 6);
    CU_ASSERT_PTR_NOT_NULL(tree);
    CU_ASSERT_EQUAL(huffman_tree_get_value(tree), 'a');
    CU_ASSERT_EQUAL(huffman_tree_get_weight(tree), 6);
    huffman_tree_delete(tree);
}

void test_huffman_tree_new_tree()
{
    HuffmanTree left = huffman_tree_new_leaf('a', 1);
    HuffmanTree right = huffman_tree_new_leaf('b', 2);
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
    HuffmanTree left = huffman_tree_new_leaf('a', 1);
    CU_ASSERT_TRUE(huffman_tree_is_leaf(left));
    HuffmanTree right = huffman_tree_new_leaf('b', 2);
    CU_ASSERT_TRUE(huffman_tree_is_leaf(right));
    HuffmanTree tree = huffman_tree_new_tree(left, right);
    CU_ASSERT_FALSE(huffman_tree_is_leaf(tree));
    huffman_tree_delete(tree);
}

void huffman_tree_add_tests()
{
    CU_pSuite suite = CU_add_suite("HuffmanTree", NULL, NULL);
    CU_add_test(suite, "test_huffman_tree_new_leaf", test_huffman_tree_new_leaf);
    CU_add_test(suite, "test_huffman_tree_new_tree", test_huffman_tree_new_tree);
    CU_add_test(suite, "test_huffman_tree_is_leaf", test_huffman_tree_is_leaf);
}
