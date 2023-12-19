#include "huffmanTree.h"

#include "statistics.h"

#include "huffmanTree.h"

// - Définitions

// - - Fonctions privées

// - - Fonctions publiques

HuffmanTree huffman_tree_new_leaf(char value, unsigned int weight) {

    HuffmanTree tree = malloc(sizeof(Node));

    tree->value = value;
    tree->weight = weight;
    tree->leftChild = NULL;
    tree->rightChild = NULL;

    return tree;
}

HuffmanTree huffman_tree_new_tree(HuffmanTree left, HuffmanTree right) {
    //Préconditions (vérifier non vides)
    assert(left);
    assert(right);

    HuffmanTree tree = newLeaf(Byte(0), left->weight + right->weight);
    tree->leftChild = left;
    tree->rightChild = right;

    return tree;
}

void huffman_tree_delete(HuffmanTree tree) {
    //Précondition
    assert(!tree);

    HuffmanTree tmpTree = tree;
    
    if (tmpTree->leftChild) huffman_tree_delete(&tmpTree->leftChild);

    if (tmpTree->rightChild) huffman_tree_delete(&tmpTree->rightChild);

    free(tmpTree);

    tree = NULL;
}

bool huffman_tree_is_leaf(const HuffmanTree tree) {
    //Précondtion
    assert(tree);

    return ((tree->leftChild==NULL) && (tree->rightChild==NULL));
}

char huffman_tree_get_value(const HuffmanTree tree) {
    //Préconditions
    assert(tree);
    assert(isLeaf(tree));

    return tree->value;
}

unsigned int huffman_tree_get_weight(const HuffmanTree tree) {
    //Précondtion
    assert(tree);

    return tree->weight;
}

HuffmanTree huffman_tree_get_left_child(const HuffmanTree tree) {
   //Prédonditions
    assert(tree);
    assert(!(isLeaf(tree)));

    return tree->leftChild;
}

HuffmanTree huffman_tree_get_right_child(const HuffmanTree tree) {
   //Préconditions
    assert(tree);
    assert(!(isLeaf(tree)));

    return tree->rightChild;
}

HuffmanTree* huffman_tree_from_statistic(const Statistics* statistics) {
    //Précondition
    assert(statistics);
    
    //TODO
    
    return NULL;
}