#pragma once

// - Bibliothèques 

#include "common.h"
#include "byte.h"
#include <stdio.h>

// - Déclarations

// - - Types

typedef struct node {
    byte value;
    unsigned int weight;
    struct node *leftChild;
    struct node *rightChild;
}

typedef *node huffmanTree;

// - - Fonctions


/// @brief Fonction créant une feuille à partir de sa valeur et du poids associé
/// @param value byte pour lequel on crée la feuille
/// @param weight poids (nb d'occurence) du byte dans le fichier
/// @return Un arbre d'Huffman qui est une feuille
huffmanTree newLeaf(byte value, unsigned int weight);

/// @brief Fonction créant un arbre à partir de ses fils gauche et droit
/// @param tree1 Futur fils gauhe
/// @param tree2 Futur fils droit
/// @return Un arbre d'huffman de fils gauche tree1 et droit tree2, weight prend la somme de weight tree1 et tree2, et value une valeur arbitraire (byte (0))
huffmanTree newTree(huffmanTree *tree1, huffmanTree *tree2);

/// @brief Fonction permettant de savoir si un arbe est une feuille (ie si ses fils sont vides)
/// @param tree 
/// @return Vrai si ses deux fils sont vides, faux sinon
bool isLeaf (huffmanTree *tree);

/// @brief Accesseur de la valeur d'une feuille (Précondition : Doit être une feuille)
/// @param tree 
/// @return La valeur de la feuille
byte getValue(huffmanTree *tree);

/// @brief Accesseur du poids d'un noeud
/// @param tree 
/// @return La valeur du noeud racine
unsigned int getWeight(huffmanTree *tree);

/// @brief Accesseur du fils gauche d'un arbre (Précondition : Ne doit pas être une feuille)
/// @param tree 
/// @return Le fils gauche
huffmanTree getLeftChild(huffmanTree *tree);

/// @brief Accesseur du fils droit d'un arbre (Précondition : Ne doit pas être une feuille)
/// @param tree 
/// @return Le fils droit
huffmanTree getRightChild(huffmanTree *tree);