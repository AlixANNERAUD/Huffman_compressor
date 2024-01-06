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
    assert(!coding_table_search(codingTable, key, NULL)); // Clé non présente dans la table

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
BinaryCode coding_table_get_value(const CodingTable *codingTable, Byte key)
{
    size_t index;
    assert(coding_table_search(codingTable, key, &index));
    return codingTable->entries[index].value;
}

/// @details Cette fonction effectue une recherche dichotomique dans la table de codage.
bool coding_table_search(const CodingTable *codingTable, Byte key, size_t *index)
{
    size_t left = 0, right = codingTable->length, middle = 0;
    bool found = false;
    while (!found && left != right)
    {
        middle = (left + right) / 2;
        if (key < codingTable->entries[middle].key)
            right = middle;
        else if (key > codingTable->entries[middle].key)
            left = middle + 1;
        else
            found = true;
    }
    if (index != NULL)
        *index = middle;
    return found;
}
