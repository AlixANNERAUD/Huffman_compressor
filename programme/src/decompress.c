#include "decompress.h"

#include "huffmanTree.h"
#include "statistics.h"

#include <string.h>

// - Définitions

// - - Fonctions privées

bool is_huffman_compressed_file(FILE *input)
{
    char identifier[4];
    if (fread(identifier, sizeof(char), sizeof(identifier), input) != 4)
        return false;

    if (strncmp(identifier, "HUFF", sizeof(identifier)) != 0)
        return false;
}

DecompressResult read_header(FILE *input, Statistics *statistics, size_t *size)
{
    // - Lecture de l'en-tête
    // - - Vérification de l'identifiant
    if (!is_huffman_compressed_file(input))
        return DECOMPRESS_ERROR_INVALID_HEADER;
    // - - Lecture de la taille des données compressées
    if (fread(size, sizeof(size_t), 1, input) != 1)
        return DECOMPRESS_ERROR_INVALID_HEADER;
    // - - Lecture des statistiques
    unsigned char buffer[sizeof(statistics->nbOccurrence)];
    if (fread(buffer, sizeof(unsigned char), sizeof(buffer), input) != sizeof(buffer))
        return DECOMPRESS_ERROR_INVALID_HEADER;   
    statistics_deserialize(statistics, buffer); // On désérialise les statistiques
}

DecompressResult decompress_data(FILE* input, FILE* output, const HuffmanTree* tree, size_t size) {
    while (feof(input) == 0) {
       // TODO : Implémenter la fonction


    }
}

// - - Fonctions publiques

DecompressResult decompress(FILE *input, FILE *output)
{
    // Préconditions
    assert(input != NULL);
    assert(output != NULL);

    if (ferror(input) || ferror(output))
        return DECOMPRESS_ERROR_FILE;

    if (feof(input))
        return DECOMPRESS_ERROR_PREMATURE_END_OF_FILE;

    DecompressResult result = DECOMPRESS_RESULT_OK;
    size_t size;
    Statistics statistics = statistics_create();
    result = read_header(input, &statistics, &size);

    if (result != DECOMPRESS_RESULT_OK)
        return result;

    HuffmanTree *tree = huffman_tree_from_statistic(&statistics);

    assert(tree != NULL);

    if (feof(input) != 0)
        return DECOMPRESS_ERROR_PREMATURE_END_OF_FILE;

    result = decompress_data(input, output, tree, size);

    huffman_tree_delete(tree);
 
    return result;
}

void decompress_error_to_string(DecompressResult error, char *buffer, size_t buffer_size)
{
    switch (error)
    {
    case DECOMPRESS_RESULT_OK:
        strncpy(buffer, "No error", buffer_size);
        break;
    case DECOMPRESS_ERROR_FILE:
        strncpy(buffer, "File error", buffer_size);
        break;
    case DECOMPRESS_ERROR_PREMATURE_END_OF_FILE:
        strncpy(buffer, "Premature end of file", buffer_size);
        break;
    case DECOMPRESS_ERROR_INVALID_HEADER:
        strncpy(buffer, "Invalid header", buffer_size);
        break;
    default:
        strncpy(buffer, "Unknown error", buffer_size);
        break;
    }
    return error;
}