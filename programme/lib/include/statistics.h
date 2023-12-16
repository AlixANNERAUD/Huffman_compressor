#pragma once

#define Statistics_MAX 256

#include "common.h"

typedef struct Statistics
{
    int lesElements[Statistics_MAX]; // type huffmantree
    FileSize nbOccurrence[Statistics_MAX];
} Statistics;

Statistics statistics_create();

unsigned int statistics_get_count(Statistics stat, int e);

Statistics statistics_set_count(Statistics stat, int e, unsigned int n);

Statistics statistics_increase_count(Statistics stat, int e);

/// @brief Fonction qui sérialise les statistiques dans un tableau d'octets.
/// @param stats Les statistiques
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_serialize(const Statistics* stats, unsigned char* buffer, FileSize size);

/// @brief Fonction qui désérialise les statistiques depuis un tableau d'octets.
/// @param stats Les statistiques.
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_deserialize(Statistics* stats, const unsigned char* buffer);
