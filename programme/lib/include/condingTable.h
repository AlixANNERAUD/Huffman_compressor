#pragma once

#include "common.h"

#define CODING_TABLE_MAXIMUM_SIZE 256

/// @brief Structure pair clé-valeur de la table de codage.
typedef struct {
    /// @brief Clé de la table de codage.
    char key;
    /// @brief Valeur de la table de codage.
    int value;
} CodingTableEntry;

/// @brief Structure table de codage.
typedef struct
{
    /// @brief Tableau des entrées de la table de codage.
    CodingTableEntry entries[CODING_TABLE_MAXIMUM_SIZE];
    /// @brief Nombre d'entrées dans la table de codage.
    size_t length;
} CodingTable;

/// @brief Crée une table de codage vide.
CodingTable CodingTable_create();

/// @brief Ajoute une entrée dans la table de codage.
/// @param codingTable Table de codage à modifier.
/// @param key Clé à ajouter.
/// @param value Valeur à ajouter.
void CodingTable_add(CodingTable *codingTable, char key, int value);

/// @brief Récupère la valeur associée à une clé dans la table de codage.
/// @param codingTable Table de codage à consulter.
/// @param key Clé à rechercher.
/// @return Valeur associée à la clé.
int CodingTable_get_value(const CodingTable* codingTable, char key);

/// @brief Vérifie si une clé est présente dans la table de codage.
/// @param codingTable Table de codage à consulter.
/// @param key Clé à rechercher.
/// @return TRUE si la clé est présente, FALSE sinon.
bool CodingTable_is_present(const CodingTable* codingTable, char key);
