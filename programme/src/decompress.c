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

    return true;
}

DecompressResult read_header(FILE *input, Statistics statistics)
{
    // - Lecture de l'en-tête
    // - - Vérification de l'identifiant
    if (!is_huffman_compressed_file(input))
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    // - - Lecture des statistiques
    unsigned char buffer[sizeof(Statistics) + sizeof(FileSize)];
    if (fread(buffer, sizeof(buffer), 1, input) != 1)
        return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE;
    if (!statistics_deserialize(statistics, buffer))
        return DECOMPRESS_RESULT_ERROR_INVALID_HEADER;
    return DECOMPRESS_RESULT_OK;
}

DecompressResult decompress_data(FILE *input, FILE *output, const HuffmanTree tree, FileSize fileSize)
{
    unsigned char bitReadPosition = 8;
    HuffmanTree currentTree = tree;
    Byte sourceByte = byte_create(0);

    FileSize decompressedBytes = 0;

    while (decompressedBytes < fileSize)
    {
        // - Lecture d'un octet du fichier d'entrée si on a lu tous les bits de l'octet précédent
        if (bitReadPosition > 7)
        {
            unsigned char bitsRead;
            if (fread(&bitsRead, sizeof(bitsRead), 1, input) != 1)
                return DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE;
            sourceByte = byte_create(bitsRead); // Conversion d'un naturel non signé d'un octet en octet
            bitReadPosition = 0;
        }

        // - Si c'est une feuille, on écrit la valeur de l'octet dans le fichier de sortie
        if (huffman_tree_is_leaf(currentTree))
        {                                                                        // Si c'est une feuille
            Byte destinationByte = huffman_tree_get_value(currentTree);          // On récupère la valeur de l'octet
            unsigned char naturalToWrite = byte_to_natural(destinationByte);     // Conversion d'un octet en naturel non signé d'un octet
            if (fwrite(&naturalToWrite, sizeof(naturalToWrite), 1, output) != 1) // Ecriture de l'octet dans le fichier de sortie
                return DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;
            decompressedBytes++;
            currentTree = tree; // Retour à la racine
        }
        // - Sinon, on continue de parcourir l'arbre
        else
        {
            Bit bit = byte_get_bit(sourceByte, bitReadPosition); // On récupère le bit
            if (bit == 0)
                currentTree = currentTree->leftChild;
            else
                currentTree = currentTree->rightChild;
            bitReadPosition++;
        }
    }

    return DECOMPRESS_RESULT_OK;
}

// - - Fonctions publiques

DecompressResult decompress(FILE *input, FILE *output)
{
    DecompressResult result = DECOMPRESS_RESULT_OK;
    Statistics statistics;
    statistics_initialize(statistics);
    result = read_header(input, statistics);

    if (result != DECOMPRESS_RESULT_OK)
        return result;

    HuffmanTree tree = huffman_tree_from_statistic(statistics);

    printf("TOtal count : %lu\n", statistics_get_total_count(statistics));

    result = decompress_data(input, output, tree, statistics_get_total_count(statistics));

    huffman_tree_delete(tree);

    // - Vérification du fichier décompressé en comparant les statistiques du fichier décompressé avec les statistiques du fichier compressé
    rewind(output); // On remet le curseur au début du fichier
    Statistics outputStatistics;
    if (!statistics_compute_from_file(outputStatistics, output))
    {
        printf("Error while computing statistics from decompressed file.\n");
        return DECOMPRESS_RESULT_FAILED_TO_CHECK_OUTPUT_FILE;
    }

    for (int i = 0; i < 0xFF; i++)
    {
        Byte byte = byte_create(i);
        if (statistics_get_count(statistics, byte) != statistics_get_count(outputStatistics, byte))
            printf("Expected %lu occurences of byte %d but got %lu.\n", statistics_get_count(statistics, byte), i, statistics_get_count(outputStatistics, byte));
        // return DECOMPRESS_RESULT_INCONSISTENT_DECOMPRESSED_FILE;
    }

    return result;
}

DecompressResult decompress_error_to_string(DecompressResult error, char *buffer, size_t buffer_size)
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
