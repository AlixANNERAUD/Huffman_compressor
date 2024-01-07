#include "compress.h"

#include "statistics.h"
#include "huffmanTree.h"
#include "statistics.h"
#include "codingTable.h"
#include "binaryCode.h"

#include <string.h>

// - Définitions

// - - Fonctions privées

void coding_table_from_huffman_tree_recursive(HuffmanTree tree, CodingTable *table, BinaryCode *current_code)
{
    if (huffman_tree_is_leaf(tree))
        coding_table_add(table, huffman_tree_get_value(tree), *current_code);
    else
    {
        binary_code_add_bit(current_code, BIT_0);
        coding_table_from_huffman_tree_recursive(huffman_tree_get_left_child(tree), table, current_code);
        binary_code_remove_last_bit(current_code);
        binary_code_add_bit(current_code, BIT_1);
        coding_table_from_huffman_tree_recursive(huffman_tree_get_right_child(tree), table, current_code);
        binary_code_remove_last_bit(current_code);
    }
}

CodingTable coding_table_from_huffman_tree(HuffmanTree tree)
{
    CodingTable table;
    BinaryCode code;

    table = coding_table_create();
    code = binary_code_create();
    coding_table_from_huffman_tree_recursive(tree, &table, &code);
    return table;
}

CompressResult write_header(FILE *destination, Statistics statistics)
{
    if (fprintf(destination, "HUFF") != 4) // On écrit l'identifiant
        return COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_HEADER;
    char statisticsBuffer[sizeof(Statistics) + sizeof(FileSize)];
    statistics_serialize(statistics, statisticsBuffer, sizeof(statisticsBuffer)); // On sérialise les statistiques
    if (fwrite(statisticsBuffer, sizeof(statisticsBuffer), 1, destination) != 1)  // On les écrit dans le fichier
        return COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_HEADER;
    return COMPRESS_RESULT_OK;
}

CompressResult compress_source_bytes(FILE *source, FILE *destination, CodingTable table)
{
    rewind(source);

    unsigned int i = 0; // Compteur de bits
    Byte input_byte = byte_create(0);
    Byte output_byte = byte_create(0);
    while (fread(&input_byte, sizeof(input_byte), 1, source) == 1)
    { // Tant que l'on a pas atteint la fin du fichier
        BinaryCode bc = coding_table_get_value(&table, input_byte); // Cherche dans la CT son équivalence en BC

        for (int j = 0; j < binary_code_get_length(&bc); j++)
        {
            byte_set_bit(&output_byte, i, binary_code_get_bit(&bc, j)); // On accède à chaque bit d'un code binaire dans un octet
            i++;

            if (i >= 8) // Si on a accumulé 8 bits ou qu'on est à la fin du fichier.
            {
                if (fwrite(&output_byte, sizeof(output_byte), 1, destination) != 1) // Et on écrit sa compression dans le fichier destination
                    return COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;
                
                output_byte = byte_create(0);
                i = 0;
            }
        }
    }
    if (ferror(source))
        return COMPRESS_RESULT_ERROR_FAILED_TO_READ_INPUT_FILE;

    if (i > 0 && fwrite(&output_byte, sizeof(output_byte), 1, destination) != 1) // Si on a des bits en attente, on les écrit
        return COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;
    return COMPRESS_RESULT_OK;
}

// - - Fonctions publiques

CompressResult compress(FILE *input, FILE *output)
{
    CompressResult result = COMPRESS_RESULT_OK;
    // - Calcul des statistiques
    Statistics statistics;
    if (!statistics_compute_from_file(statistics, input))
        return COMPRESS_RESULT_ERROR_FILE;
    // - Création de l'arbre de Huffman
    HuffmanTree huffmanTree;
    huffmanTree = huffman_tree_from_statistic(statistics);
    // - Création de la table de codage
    CodingTable codingTable;
    codingTable = coding_table_from_huffman_tree(huffmanTree);
    huffman_tree_delete(huffmanTree); // On libère la mémoire de l'arbre de Huffman
    // - Écriture de l'en-tête
    result = write_header(output, statistics);
    if (result != COMPRESS_RESULT_OK)
        return result;
    // - Compression des données
    return compress_source_bytes(input, output, codingTable);
}
