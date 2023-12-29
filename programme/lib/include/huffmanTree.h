#pragma once

// - Bibliothèques 

#include "common.h"
#include "byte.h"
#include <stdio.h>


// - Déclarations

// - - Types

/// @brief 
typedef struct Node {
    /// @brief Valeur (byte) du noeud. NB : Utile uniquement dans une feuille. 
    Byte value;
    /// @brief Poids du noeud, son poids propre s'il est une feuille, la somme du poids de ses fils sinon. 
    unsigned int weight;
    /// @brief Fils gauche.
    struct Node* leftChild;
    /// @brief Fils droit.
    struct Node* rightChild;
} Node;

typedef Node* HuffmanTree;

// - - Fonctions

/// @brief Fonction créant une feuille à partir de sa valeur et du poids associé
/// @param value Byte pour lequel on crée la feuille
/// @param weight poids (nb d'occurence) du Byte dans le fichier
/// @return Un arbre d'Huffman qui est une feuille
HuffmanTree huffman_tree_new_leaf(char value, unsigned int weight);

/// @brief Fonction créant un arbre à partir de ses fils gauche et droit
/// @param tree1 Futur fils gauhe
/// @param tree2 Futur fils droit
/// @return Un arbre d'huffman de fils gauche tree1 et droit tree2, weight prend la somme de weight tree1 et tree2, et value une valeur arbitraire (Byte (0))
HuffmanTree huffman_tree_new_tree(HuffmanTree left, HuffmanTree right);

/// @brief Fonction permettant de savoir si un arbe est une feuille (ie si ses fils sont vides)
/// @param tree 
/// @return Vrai si ses deux fils sont vides, faux sinon
bool huffman_tree_is_leaf(const HuffmanTree tree);

/// @brief Accesseur de la valeur d'une feuille (Précondition : Doit être une feuille)
/// @param tree 
/// @return La valeur de la feuille
char huffman_tree_get_value(const HuffmanTree tree);

/// @brief Accesseur du poids d'un noeud
/// @param tree 
/// @return La valeur du noeud racine
unsigned int huffman_tree_get_weight(const HuffmanTree tree);

/// @brief Accesseur du fils gauche d'un arbre (Précondition : Ne doit pas être une feuille)
/// @param tree 
/// @return Le fils gauche
HuffmanTree huffman_tree_get_left_child(const HuffmanTree tree);

/// @brief Accesseur du fils droit d'un arbre (Précondition : Ne doit pas être une feuille)
/// @param tree 
/// @return Le fils droit
HuffmanTree huffman_tree_get_right_child(const HuffmanTree tree);

/// @brief Fonction permettant de comparer deux arbres d'Huffman (utilisée pour la file de priorité)
/// @param tree1 Arbre 1
/// @param tree2 Arbre 2
/// @return Vrai si tree1 est considéré comme plus grand que tree2, faux sinon
bool huffman_tree_greater_than(HuffmanTree tree1, HuffmanTree tree2);

void huffman_tree_delete(HuffmanTree tree);

typedef struct Statistics Statistics; // Déclaration anticipée pour réduire les dépendances inter-fichiers.

typedef struct PriorityQueue PriorityQueue; // De même 

HuffmanTree* huffman_tree_from_statistic(const Statistics *statistics); // Transtypage
