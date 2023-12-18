#include "huffmanTree.h"

// - Définitions

// - - Fonctions privées


// - - Fonctions publiques


huffmanTree newLeaf(Byte value, unsigned int weight)
{
    huffmanTree *tree = malloc(sizeof(node));

    tree->value = value;
    tree->weight = weight;
    tree->*leftChild = NULL;
    tree->*rightChild = NULL;

    return tree;
}

huffmanTree newTree(huffmanTree *tree1, huffmanTree *tree2)
{
    huffmanTree *tree = newLeaf(Byte(0), tree1->weight + tree2->weight);
    tree->*leftChild = *tree1;
    tree->*rightChild = *tree2;

    return *tree;
}

bool isLeaf (huffmanTree *tree)
{
    return ((tree->*leftChild==NULL) && (tree->*rightChild==NULL));
}

Byte getValue(huffmanTree *tree)
{
    //Précondition
    assert(isLeaf(tree));

    return tree->value;
}

unsigned int getWeight(huffmanTree *tree)
{
    return tree->weight;
}

huffmanTree getLeftChild(huffmanTree *tree)
{
    //Prédondition
    assert(!(isLeaf(tree)));

    return tree->*leftChild;
}

huffmanTree getRightChild(huffmanTree *tree)
{
    //Précondition
    assert(!(isLeaf(tree)));

    return tree->*rightChild;
}