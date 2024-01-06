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

#include "stdio.h"
#include "common.h"
#include "byte.h"

/// @brief Type Statistique qui est un tableau de type `FileSize` de taille STATISTICS_MAX + 1.
/// @details Les 256 premières cases du tableau correspondent aux statistiques de chaque octet.
/// La dernière case du tableau correspond à la taille du fichier.
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
FileSize statistics_get_count(const Statistics stat, Byte e);

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
void statistics_increment_count(Statistics stat, Byte e);

/// @brief Fonction qui renvoie la taille du fichier.
/// @param stat Les statistiques
/// @return La taille du fichier.
FileSize statistics_get_file_size(const Statistics stat);

/// @brief Fonction qui calcule les statistiques à partir d'un fichier.
/// @param statistics Les statistiques résultantes.
/// @param file Le fichier d'entrée ouvert en lecture.
/// @return Si le calcul s'est bien passé.
bool statistics_compute_from_file(Statistics stat, FILE* file);

/// @brief Fonction qui sérialise les statistiques dans un tableau d'octets.
/// @param stats Les statistiques
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_serialize(const Statistics stats, void* buffer, FileSize size);

/// @brief Fonction qui désérialise les statistiques depuis un tableau d'octets.
/// @param stats Les statistiques.
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
bool statistics_deserialize(Statistics stats, const void* buffer);

