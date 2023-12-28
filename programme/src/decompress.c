#include "decompress.h"

#include "huffmanTree.h"
#include "statistics.h"
#include "binaryCode.h"

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

DecompressResult read_header(FILE *input, Statistics *statistics, FileSize *size)
{
    // - Lecture de l'en-tête
    // - - Vérification de l'identifiant
    if (!is_huffman_compressed_file(input))
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    // - - Lecture de la taille des données compressées
    if (fread(size, sizeof(FileSize), 1, input) != 1)
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    // - - Lecture des statistiques
    unsigned char buffer[sizeof(statistics->nbOccurrence)];
    if (fread(buffer, sizeof(unsigned char), sizeof(buffer), input) != sizeof(buffer))
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    statistics_deserialize(statistics, buffer); // On désérialise les statistiques
}

DecompressResult decompress_data(FILE *input, FILE *output, const HuffmanTree tree, FileSize *decompressedSize)
{
    unsigned char bitReadPosition = 0;
    HuffmanTree currentTree = tree;
    Byte sourceByte = byte_create(0);
    decompressedSize = 0;

    while (feof(input) == 0)
    {
        //BinaryCode code = binary_code_create();
        if (bitReadPosition > 7)
        {
            unsigned char bitsRead;
            if (fread(&bitsRead, sizeof(bitsRead), 1, input) != 1)
                return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE; // Lecture du nombre de bits à lire
            sourceByte = byte_create(bitsRead);                       // Conversion d'un naturel non signé d'un octet en octet
            bitReadPosition = 0;
        }

        if (huffman_tree_is_leaf(currentTree))
        {                                                        // Si c'est une feuille
            Bit bit = byte_get_bit(sourceByte, bitReadPosition); // On récupère le bit
            if (bit == 0)
                currentTree = currentTree->leftChild;
            else
                currentTree = currentTree->rightChild;
            bitReadPosition++;
        }
        else
        {
            Byte destinationByte = huffman_tree_get_value(currentTree);           // On récupère la valeur de l'octet
            unsigned char naturalToWrite = byte_to_natural(destinationByte);      // Conversion d'un octet en naturel non signé d'un octet
            if (fwrite(&output, sizeof(naturalToWrite), 1, &naturalToWrite) != 1) // Ecriture de l'octet dans le fichier de sortie
                return DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;
            currentTree = tree; // Retour à la racine
            *decompressedSize++;
        }
    }

    return DECOMPRESS_RESULT_OK;
}

// - - Fonctions publiques

DecompressResult decompress(FILE *input, FILE *output)
{
    // Préconditions
    assert(input != NULL);
    assert(output != NULL);

    if (ferror(input) || ferror(output))
        return DECOMPRESS_RESULT_ERROR_FILE;

    if (feof(input))
        return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE;

    DecompressResult result = DECOMPRESS_RESULT_OK;
    FileSize size;
    Statistics statistics = statistics_create();
    result = read_header(input, &statistics, &size);

    if (result != DECOMPRESS_RESULT_OK)
        return result;

    HuffmanTree *tree = huffman_tree_from_statistic(&statistics);

    assert(tree != NULL);

    if (feof(input) != 0)
        return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE;

    result = decompress_data(input, output, *tree, &size);

    huffman_tree_delete(*tree);

    return result;
}

DecompressResult decompress_error_to_string(DecompressResult error, char *buffer, FileSize buffer_size)
{
    switch (error)
    {
    case DECOMPRESS_RESULT_OK:
        strncpy(buffer, "No error", buffer_size);
        break;
    case DECOMPRESS_RESULT_ERROR_FILE:
        strncpy(buffer, "File error", buffer_size);
        break;
    case DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE:
        strncpy(buffer, "Premature end of file", buffer_size);
        break;
    case DECOMPRESS_RESULT_ERROR_INVALID_HEADER:
        strncpy(buffer, "Invalid header", buffer_size);
        break;
    case DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE:
        strncpy(buffer, "Failed to write output file", buffer_size);
        break;
    case DECOMPRESS_RESULT_INCONSISTENT_DECOMPRESSED_FILE:
        strncpy(buffer, "Inconsistent decompressed file", buffer_size);
        break;
    default:
        strncpy(buffer, "Unknown error", buffer_size);
        break;
    }
    return error;
}
