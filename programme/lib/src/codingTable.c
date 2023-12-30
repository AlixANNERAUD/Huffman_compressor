#include "codingTable.h"


CodingTable coding_table_create()
{
    CodingTable codingTable;
    codingTable.length = 0;
    return codingTable;
}

/// @details Cette fonction ajoute un ensemble clé-valeur dans la table de codage.
/// Cette fonction ne doit pas être appelée si la clé est déjà présente dans la table.
/// La table étant ordonnée, la recherche d'un clé se font en O(log(n)), accélérant ainsi la compression.
/// Cependant, la recherche d'une valeur se fait en O(n) car la table n'est pas indexée par valeur
void coding_table_add(CodingTable *codingTable, Byte key, BinaryCode value)
{
    // Préconditions

    assert(codingTable); // Pointeur non nul
    assert(!coding_table_is_present(codingTable, key));

    size_t i = codingTable->length;
    // On décale les éléments de la table pour insérer le nouvel élément
    while (codingTable->entries[i - 1].key > key && i > 0)
    {
        codingTable->entries[i] = codingTable->entries[i - 1];
        i--;
    }

    // On insère le nouvel élément
    codingTable->entries[i].key = key;
    codingTable->entries[i].value = value;
    codingTable->length++;
}

/// @details Cette fonction vérifie si une clé est présente dans la table de codage.
/// La recherche est effectuée par dichotomie, ce qui permet d'effectuer la recherche en O(log(n)) 
BinaryCode coding_table_get_value(const CodingTable* codingTable, Byte key)
{
    // Préconditions
    assert(codingTable != NULL);
    assert(coding_table_is_present(codingTable, key));

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

bool coding_table_is_present(const CodingTable* codingTable, Byte key)
{
    // Préconditions
    assert(codingTable); // Pointeur non null

    if (codingTable->length == 0)   // Si la table est vide, la clé n'est pas présente (et on évite un débordement d'entier)
        return false;
    

    size_t left = 0;
    size_t right = codingTable->length - 1;
    size_t middle = (left + right) / 2;

   // printf("left: %zu, right: %zu, middle: %zu\n", left, right, middle);

    while (left < right && codingTable->entries[middle].key != key)
    {
        if (codingTable->entries[middle].key > key)
        {
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
        middle = (left + right) / 2;
    }

    return codingTable->entries[middle].key == key;
}
