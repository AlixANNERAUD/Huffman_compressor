/**
 * @file binaryCode.h
 * fichier de déclaration du TAD Code Binaire
*/

#pragma once

#include "common.h"

#include "bit.h"

/**
 * @def BinaryCode_MAX
 * La taille maximale d'un code binaire
*/
#define BinaryCode_MAX 1000

/**
 * @struct BinaryCode
 * Structure représentant un code binaire comme un tableau de Bits de longueur length
*/
typedef struct {
    /// @brief Tableau de Bits
    Bit bits[BinaryCode_MAX]; 
    /// @brief Longueur du tableau
    unsigned int length;
} BinaryCode;

/**
 * @fn BinaryCode binary_code_create()
 * @brief Fonction qui crée un code binaire
*/
BinaryCode binary_code_create();

/**
 * @fn unsigned int binary_code_get_length(const BinaryCode* binaryCode)
 * @brief Fonction qui renvoie la longueur d'un code bianire
 * @param binarycode Le code binaire
*/
unsigned int binary_code_get_length(const BinaryCode* binaryCode);

/**
 * @fn Bit binary_code_get_bit(const BinaryCode* binaryCode, unsigned int index)
 * @brief Fonction qui renvoie le Bit à un certain indice d'un code binaire
 * @param binaryCode Le code binaire
 * @param index L'indice du Bit que l'on souhaite obtenir
*/
Bit binary_code_get_bit(const BinaryCode* binaryCode, unsigned int index);

/**
 * @fn void binary_code_add_bit(BinaryCode* binaryCode, Bit bit)
 * @brief Fonction qui ajoute un Bit à la fin d'un code binaire
 * @param binaryCode Le code binaire
 * @param bit Le Bit que l'on souhaite ajouter
*/
void binary_code_add_bit(BinaryCode* binaryCode, Bit bit);

/**
 * @fn void binary_code_remove_bit(BinaryCode* binaryCode, unsigned int index)
 * @brief Fonction qui efface un Bit à un certain indice dans un code binaire
 * @param binaryCode Le code binaire
 * @param index L'indice du bit à effacer
*/
void binary_code_remove_bit(BinaryCode* binaryCode, unsigned int index);

/**
 * @fn void binary_code_remove_last_bit(BinaryCode* binaryCode)
 * @brief Fonction qui efface le dernier Bit d'un code binaire
 * @param binaryCode Le code binaire
*/
void binary_code_remove_last_bit(BinaryCode* binaryCode);
