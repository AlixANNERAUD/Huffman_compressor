#include "condingTable.h"

CodingTable CodingTable_create()
{
    CodingTable codingTable;
    codingTable.length = 0;
    return codingTable;
}

/// @details Cette fonction ajoute un ensemble clé-valeur dans la table de codage.
/// Cette fonction ne doit pas être appelée si la clé est déjà présente dans la table.
/// La table étant ordonnée, l'insertion et la recherche d'un clé se font en O(log(n)), accélérant ainsi la compression.
/// Cependant, la recherche d'une valeur se fait en O(n) car la table n'est pas indexée par valeur
void CodingTable_add(CodingTable *codingTable, char key, int value)
{
    // Préconditions
    assert(codingTable != NULL);
    assert(CodingTable_is_present(codingTable, key));
   
    size_t i = codingTable->length;
    // On décale les éléments de la table pour insérer le nouvel élément
    while (codingTable->entries[i].key > key && i > 0)
    {
        codingTable->entries[i + 1] = codingTable->entries[i];
        i--;
    }

    // On insère le nouvel élément
    codingTable->entries[i].key = key;
    codingTable->entries[i].value = value;
    codingTable->length++;
}

/// @details Cette fonction vérifie si une clé est présente dans la table de codage.
/// La recherche est effectuée par dichotomie, ce qui permet d'effectuer la recherche en O(log(n)) 
int CodingTable_get_value(const CodingTable* codingTable, char key)
{
    // Préconditions
    assert(codingTable != NULL);
    assert(CodingTable_is_present(codingTable, key));

    size_t min = 0;
    size_t max = codingTable->length - 1;
    size_t mid = (min + max) / 2;

    while (codingTable->entries[mid].key != key)
    {
        if (codingTable->entries[mid].key > key)
        {
            max = mid - 1;
        }
        else
        {
            min = mid + 1;
        }
        mid = (min + max) / 2;
    }

    return codingTable->entries[mid].value;
}

bool CodingTable_is_present(const CodingTable* codingTable, char key)
{
    // Préconditions
    assert(codingTable != NULL);

    size_t min = 0;
    size_t max = codingTable->length - 1;
    size_t mid = (min + max) / 2;

    while (min <= max && codingTable->entries[mid].key != key)
    {
        if (codingTable->entries[mid].key > key)
        {
            max = mid - 1;
        }
        else
        {
            min = mid + 1;
        }
        mid = (min + max) / 2;
    }

    return codingTable->entries[mid].key == key;
}