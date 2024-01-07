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
    memset(stat, 0, sizeof(Statistics)); // On met tout à 0
}

FileSize statistics_get_count(const Statistics stat, Byte e)
{
    return stat[byte_to_natural(e)];
}

void statistics_set_count(Statistics stat, Byte e, unsigned int n)
{
    stat[byte_to_natural(e)] = n;
}

void statistics_increment_count(Statistics stat, Byte e)
{
    stat[byte_to_natural(e)]++;
}

FileSize statistics_get_total_count(const Statistics stat)
{
    FileSize Sum = 0;
    for (int i = 0; i < STATISTICS_MAX; i++)
        Sum += stat[i];
    return Sum;
}

bool statistics_compute_from_file(Statistics statistics, FILE *file)
{
    statistics_initialize(statistics);
    Byte byte = byte_create(0);
    while (fread(&byte, sizeof(byte), 1, file) == 1)
        statistics_increment_count(statistics, byte);

    return !ferror(file);
}

bool statistics_are_equals(const Statistics statistics1, const Statistics statistics2)
{
    return memcmp(statistics1, statistics2, sizeof(Statistics)) == 0; // Plus rapide que de faire une boucle for
}

/// @details Fonction qui copie simplement octet par octet les statistiques dans le buffer.
void statistics_serialize(const Statistics stats, void *buffer, FileSize size)
{
    // Préconditions
    assert(stats != NULL);
    assert(buffer != NULL);
    assert(size == sizeof(Statistics) + sizeof(FileSize));

    uint8_t* byteBuffer = (uint8_t*)buffer; // On cast le buffer en tableau d'octets pour éviter de faire des calculs de pointeurs (provoque des warnings)
    FileSize fileSize = statistics_get_total_count(stats);
    memcpy(byteBuffer, &fileSize, sizeof(fileSize)); // On copie la taille du fichier
    memcpy(&byteBuffer[sizeof(FileSize)], stats, sizeof(Statistics));   // On copie les statistiques
}

/// @details Fonction qui copie simplement octet par octet le buffer dans les statistiques.
bool statistics_deserialize(Statistics stats, const void *buffer)
{
    // Préconditions
    assert(stats != NULL);
    assert(buffer != NULL);
    assert(strlen((const char *)buffer) != sizeof(Statistics));

    const uint8_t* byteBuffer = (const uint8_t*)buffer; // On cast le buffer en tableau d'octets pour éviter de faire des calculs de pointeurs (provoque des warnings)
    FileSize fileSize = 0;
    memcpy(&fileSize, byteBuffer, sizeof(FileSize));                  // On copie la taille du fichier                                  // On décale le buffer de la taille du type FileSize
    memcpy(stats, &byteBuffer[sizeof(FileSize)], sizeof(Statistics)); // On copie les statistiques

    return fileSize == statistics_get_total_count(stats);
}
