#ifndef STATISTICS_H_DEFINED
#define STATISTICS_H_DEFINED

#define Statistics_MAX 256

#include "common.h"

typedef struct
{
    int lesElements[Statistics_MAX]; // type huffmantree
    unsigned int nbOccurrence[Statistics_MAX];
} Statistics;

Statistics Statistics_statistics();

unsigned int Statistics_getCount(Statistics stat, int e);

Statistics Statistics_setCount(Statistics stat, int e, unsigned int n);

Statistics Statistics_increaseCount(Statistics stat, int e);

/// @brief Fonction qui sérialise les statistiques dans un tableau d'octets.
/// @param stats Les statistiques
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_serialize(const Statistics* stats, unsigned char* buffer, FileSize size);

/// @brief Fonction qui désérialise les statistiques depuis un tableau d'octets.
/// @param stats Les statistiques.
/// @param buffer Le buffer d'une taille de 64 * 256 = 2048 octets.
void statistics_deserialize(Statistics* stats, const unsigned char* buffer);

#endif // STATISTICS_H_DEFINED