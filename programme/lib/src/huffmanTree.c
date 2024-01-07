// - Dépendances
// - - Librairie standard
#include <stdlib.h> // Pour malloc et free (include <malloc.h> ne fonctionne pas, au moins sous mac)
// - - Locales
#include "huffmanTree.h"
#include "statistics.h"
#include "priorityQueue.h"

// - Définitions

// - - Fonctions publiques

HuffmanTree huffman_tree_new_leaf(Byte value, FileSize weight)
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
    HuffmanTree tree = huffman_tree_new_leaf(byte_create(0), huffman_tree_get_weight(left) + huffman_tree_get_weight(right));
    tree->leftChild = left;
    tree->rightChild = right;
    return tree;
}

void huffman_tree_delete(HuffmanTree tree)
{
    if (tree->leftChild) // Si le pointeur n'est pas nul
        huffman_tree_delete(tree->leftChild);
    if (tree->rightChild) // Si le pointeur n'est pas nul
        huffman_tree_delete(tree->rightChild);
    free(tree); // On libère la mémoire du pointeur courant
}

bool huffman_tree_is_leaf(const HuffmanTree tree)
{
    return ((tree->leftChild == NULL) && (tree->rightChild == NULL));
}

Byte huffman_tree_get_value(const HuffmanTree tree)
{
    // Préconditions
    assert(huffman_tree_is_leaf(tree));
    return tree->value;
}

FileSize huffman_tree_get_weight(const HuffmanTree tree)
{
    return tree->weight;
}

HuffmanTree huffman_tree_get_left_child(const HuffmanTree tree)
{
    // Préconditions
    assert(!huffman_tree_is_leaf(tree));
    return tree->leftChild;
}

HuffmanTree huffman_tree_get_right_child(const HuffmanTree tree)
{
    // Préconditions
    assert(!(huffman_tree_is_leaf(tree)));
    return tree->rightChild;
}

HuffmanTree huffman_tree_from_statistic(const Statistics stat)
{
    PriorityQueue queue = priority_queue_create();
    // - On converti les statistiques en feuilles pour les ajouter à la file de priorité
    for (unsigned int i = 0; i <= 0xFF; i++)
    {
        FileSize count = statistics_get_count(stat, byte_create(i));
        if (count > 0)
        {
            HuffmanTree leaf = huffman_tree_new_leaf(byte_create(i), count);
            priority_queue_push(&queue, leaf);
        }
    }
    // - On construit l'arbre de Huffman en fusionnant les feuilles en partant des plus petites (fin de la file de priorité)
    HuffmanTree tree, rightLeaf, leftLeaf;
    while (priority_queue_get_length(&queue) > 1)
    {
        leftLeaf = priority_queue_pop(&queue);
        if (priority_queue_get_length(&queue) > 0)
        {
            rightLeaf = priority_queue_pop(&queue);
            tree = huffman_tree_new_tree(leftLeaf, rightLeaf);
        }
        else
            tree = leftLeaf; // Si il n'y a plus qu'une feuille, on la prend 

        priority_queue_push(&queue, tree); // On ajoute l'arbre à la file de priorité
    }
    return tree;
}

bool huffman_tree_greater_than(HuffmanTree tree1, HuffmanTree tree2)
{
    if (huffman_tree_get_weight(tree1) > huffman_tree_get_weight(tree2)) // Si le poids de tree1 est plus grand que celui de tree2, on retourne vrai
        return true;

    if (huffman_tree_get_weight(tree1) == huffman_tree_get_weight(tree2) && huffman_tree_is_leaf(tree1) && huffman_tree_is_leaf(tree2)) // Si les poids sont égaux et que les deux arbres sont des feuilles, on compare les valeurs
        return (huffman_tree_get_value(tree1) > huffman_tree_get_value(tree2));

    return false; // Valeur par défaut
}
