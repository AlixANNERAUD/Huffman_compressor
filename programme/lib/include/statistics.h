/**
 * @file statistique.h
 * fichier de déclaration du TAD Statistique
*/

#pragma once

/**
 * @def Statistics_MAX
 * La taille maximale du TAD Statistique
*/
#define Statistics_MAX 256

#include "common.h"
#include "binaryCode.h"

/**
 * @struct Statistics
 * Structure associant chaque élément à son nombre d'occurence
*/
typedef struct Statistics
{
    ///@brief Tableau des Codes Binaires représentant les éléments
    BinaryCode lesElements[Statistics_MAX];
    /// @brief Tableau des nombres d'occurences de chaque élément
    unsigned int nbOccurrence[Statistics_MAX];
} Statistics;

/**
 * @fn Statistics statistics_create()
 * @brief Fonction qui crée un TAD Statistique
*/
Statistics statistics_create();

/**
 * @fn unsigned int statistics_get_count(Statistics stat, BinaryCode e)
 * @brief Fonction qui renvoie le nombre d'occurence d'un élément e
 * @param stat Les statistiques
 * @param e élément sous forme de code binaire
*/
unsigned int statistics_get_count(const Statistics* stat, BinaryCode e);

/**
 * @fn statistics_set_count(Statistics* stat, BinaryCode e, unsigned int n)
 * @brief Fonction qui permet de définir le nombre d'occurences d'un élément e
 * @param stat Les statistiques
 * @param e élément sous forme de code binaire
 * @param n Nombre d'occurences de e
*/
void statistics_set_count(Statistics* stat, BinaryCode e, unsigned int n);

/**
 * @fn statistics_increase_count(Statistics* stat, BinaryCode e)
 * @brief Fonction qui permet d'augmenter de 1 le nombre d'occurence d'un élément e
 * @param stat Les statistiques
 * @param e élément sous forme de code binaire
*/
void statistics_increase_count(Statistics* stat, BinaryCode e);

/// @brief Fonction qui sérialise les statistiques dans un tableau d'octets.
/// @param stats Les statistiques
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_serialize(const Statistics* stats, unsigned char* buffer, FileSize size);

/// @brief Fonction qui désérialise les statistiques depuis un tableau d'octets.
/// @param stats Les statistiques.
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_deserialize(Statistics* stats, const unsigned char* buffer);
