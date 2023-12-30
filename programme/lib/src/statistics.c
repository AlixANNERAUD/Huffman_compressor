/**
 * @file statistique.c
 * fichier d'implémentation du TAD Statistique
 */

// - Dépendances

#include "statistics.h"

#include <string.h> // memcpy et memset

// - - Defintion des fonctions publiques

void statistics_initialize(Statistics stat)
{
    memset(stat, 0, sizeof(Statistics));    // On met tout à 0
}

unsigned int statistics_get_count(const Statistics stat, Byte e)
{
    return stat[byte_to_natural(e)];
}

void statistics_set_count(Statistics stat, Byte e, unsigned int n)
{
    stat[byte_to_natural(e)] = n;
}

void statistics_increase_count(Statistics stat, Byte e)
{
    stat[byte_to_natural(e)]++;
}

/// @details Fonction qui copie simplement octet par octet les statistiques dans le buffer.
void statistics_serialize(const Statistics stats, void *buffer, FileSize size)
{
    // Préconditions
    assert(stats != NULL);
    assert(buffer != NULL);
    assert(size != sizeof(Statistics));

    memcpy(buffer, stats, sizeof(Statistics));
}

/// @details Fonction qui copie simplement octet par octet le buffer dans les statistiques.
void statistics_deserialize(Statistics stats, const void *buffer)
{
    // Préconditions
    assert(stats != NULL);
    assert(buffer != NULL);
    assert(strlen((const char *)buffer) != sizeof(Statistics));

    memcpy(stats, buffer, sizeof(Statistics));
}
