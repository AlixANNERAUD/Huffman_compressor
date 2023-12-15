#ifndef HUFFMAN_TREE_H_DEFINED
#define HUFFMAN_TREE_H_DEFINED

#include "common.h"

typedef struct {
// TODO : A compléter
} HuffmanTree;

HuffmanTree* HuffmanTree_new_leaf(char value, unsigned int weight);

HuffmanTree* HuffmanTree_new_tree(HuffmanTree *left, HuffmanTree *right);

void HuffmanTree_delete(HuffmanTree *tree);

bool HuffmanTree_is_leaf(const HuffmanTree *tree);

char HuffmanTree_get_value(const HuffmanTree *tree);

unsigned int HuffmanTree_get_weight(const HuffmanTree *tree);

HuffmanTree* HuffmanTree_get_left_child(const HuffmanTree *tree);

HuffmanTree* HuffmanTree_get_right_child(const HuffmanTree *tree);

#endif // HUFFMAN_TREE_H_DEFINED