#include "huffmanTree.h"

#include "statistics.h"

#include "priorityQueue.h"

#include <stdlib.h> // Pour malloc et free (include <malloc.h> ne fonctionne pas, au moins sous mac)

// - Définitions

// - - Fonctions privées

// - - Fonctions publiques

HuffmanTree huffman_tree_new_leaf(Byte value, unsigned int weight)
{

    HuffmanTree tree = malloc(sizeof(Node));

    tree->value = value;
    tree->weight = weight;
    tree->leftChild = NULL;
    tree->rightChild = NULL;

    return tree;
}

HuffmanTree huffman_tree_new_tree(HuffmanTree left, HuffmanTree right)
{
    // Préconditions (vérifier non vides)
    assert(left);
    assert(right);

    HuffmanTree tree = huffman_tree_new_leaf(byte_create(0), 0);
    tree->leftChild = left;
    tree->rightChild = right;

    return tree;
}

void huffman_tree_delete(HuffmanTree tree)
{
    // Précondition
    assert(tree);

    HuffmanTree tmpTree = tree;

    if (tmpTree->leftChild)
        huffman_tree_delete(tmpTree->leftChild);

    if (tmpTree->rightChild)
        huffman_tree_delete(tmpTree->rightChild);

    free(tmpTree);

    tree = NULL;
}

bool huffman_tree_is_leaf(const HuffmanTree tree)
{
    // Précondtion
    assert(tree);

    return ((tree->leftChild == NULL) && (tree->rightChild == NULL));
}

Byte huffman_tree_get_value(const HuffmanTree tree)
{
    // Préconditions
    assert(tree);
    assert(huffman_tree_is_leaf(tree));

    return tree->value;
}

unsigned int huffman_tree_get_weight(const HuffmanTree tree)
{
    // Précondtion
    assert(tree);

    return tree->weight;
}

HuffmanTree huffman_tree_get_left_child(const HuffmanTree tree)
{
    // Prédonditions
    assert(tree);
    assert(!huffman_tree_is_leaf(tree));

    return tree->leftChild;
}

HuffmanTree huffman_tree_get_right_child(const HuffmanTree tree)
{
    // Préconditions
    assert(tree);
    assert(!(huffman_tree_is_leaf(tree)));

    return tree->rightChild;
}

HuffmanTree *huffman_tree_from_statistic(const Statistics *stat)
{
    // Précondition
    assert(stat);

    HuffmanTree tree;
    HuffmanTree leaf;
    HuffmanTree rightLeaf;
    HuffmanTree leftLeaf;
    Byte byte;
    FileSize count;
    PriorityQueue queue = priority_queue_create();

    for (FileSize i=0;i<256;i++){
        count = stat[i];
        if(count>0){
            leaf = huffman_tree_new_leaf(byte_create(i), count);
            priority_queue_push(queue, leaf);
        }
    }
    while ((priority_queue_get_length)>0){
        leftLeaf = priority_queue_pop(&queue);
        if ((priority_queue_get_length)>0){
            rightLeaf = priority_queue_pop(&queue);
            tree = huffman_tree_new_tree(leftLeaf, rightLeaf);
        }
        else {
            tree = leftLeaf;
        }
    }
    return tree;
}

bool huffman_tree_greater_than(HuffmanTree tree1, HuffmanTree tree2)
{
    // Préconditions
    assert(tree1);
    assert(tree2);

    if (huffman_tree_get_weight(tree1) > huffman_tree_get_weight(tree2))    // Si le poids de tree1 est plus grand que celui de tree2, on retourne vrai
        return true;

    if (huffman_tree_get_weight(tree1) == huffman_tree_get_weight(tree2) && huffman_tree_is_leaf(tree1) && huffman_tree_is_leaf(tree2)) // Si les poids sont égaux et que les deux arbres sont des feuilles, on compare les valeurs
        return (huffman_tree_get_value(tree1) > huffman_tree_get_value(tree2));

    return false;
}
