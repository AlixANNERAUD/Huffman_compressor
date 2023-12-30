/**
 * @file statistique.h
 * fichier de déclaration du TAD Statistique
*/

#pragma once

/**
 * @def STATISTICS_MAX
 * La taille maximale du TAD Statistique
*/
#define STATISTICS_MAX 256

#include "common.h"
#include "byte.h"

typedef FileSize Statistics[STATISTICS_MAX];

/**
 * @fn Statistics statistics_create()
 * @brief Fonction qui crée un TAD Statistique
*/
void statistics_initialize(Statistics stat);

/**
 * @fn unsigned int statistics_get_count(Statistics stat, Byte e)
 * @brief Fonction qui renvoie le nombre d'occurence d'un élément e
 * @param stat Les statistiques
 * @param e élément sous forme d'octet
*/
unsigned int statistics_get_count(const Statistics stat, Byte e);

/**
 * @fn statistics_set_count(Statistics* stat, Byte e, unsigned int n)
 * @brief Fonction qui permet de définir le nombre d'occurences d'un élément e
 * @param stat Les statistiques
 * @param e élément sous forme d'octet
 * @param n Nombre d'occurences de e
*/
void statistics_set_count(Statistics stat, Byte e, unsigned int n);

/**
 * @fn statistics_increase_count(Statistics* stat, Byte e)
 * @brief Fonction qui permet d'augmenter de 1 le nombre d'occurence d'un élément e
 * @param stat Les statistiques
 * @param e élément sous forme d'octet
*/
void statistics_increase_count(Statistics stat, Byte e);

/// @brief Fonction qui sérialise les statistiques dans un tableau d'octets.
/// @param stats Les statistiques
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_serialize(const Statistics stats, void* buffer, FileSize size);

/// @brief Fonction qui désérialise les statistiques depuis un tableau d'octets.
/// @param stats Les statistiques.
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_deserialize(Statistics stats, const void* buffer);
