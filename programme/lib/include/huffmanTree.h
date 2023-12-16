#pragma once

#include "common.h"

typedef struct {
// TODO : A compléter
} HuffmanTree;


HuffmanTree* huffman_tree_new_leaf(char value, unsigned int weight);

HuffmanTree* huffman_tree_new_tree(HuffmanTree *left, HuffmanTree *right);

void huffman_tree_delete(HuffmanTree *tree);

bool huffman_tree_is_leaf(const HuffmanTree *tree);

char huffman_tree_get_value(const HuffmanTree *tree);

unsigned int huffman_tree_get_weight(const HuffmanTree *tree);

HuffmanTree* huffman_tree_get_left_child(const HuffmanTree *tree);

HuffmanTree* huffman_tree_get_right_child(const HuffmanTree *tree);

typedef struct Statistics; // Déclaration anticipée pour réduire les dépendances inter-fichiers.

HuffmanTree* huffman_tree_from_statistic(const Statistics *statistics); // Transtypage