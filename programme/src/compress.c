// - Dépendances
// - - Librairie standard
#include <string.h> // strncmp
// - - Locales
#include "statistics.h"
#include "huffmanTree.h"
#include "statistics.h"
#include "codingTable.h"
#include "binaryCode.h"
#include "compress.h"
#include "progressBar.h"

// - Définitions

// - - Fonctions privées

/// @brief Fonction utilisée dans coding_table_from_huffman_tree, construit la table de codage en fonction de l'abre d'Huffman.
/// @details Utilise l'abre d'Huffman pour généré l'équivalent en code binaire de chaque feuille (bit du fichier en entrée) de l'abre, et le stocker dans la table de codage.
/// @param tree Arbre d'Huffman courrant.
/// @param table Table de codage.
/// @param current_code Code binaire en construction, inscrit dans la table de codage une fois une feuille atteinte.
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

/// @brief Fonction construisant la table de codage en fonction de l'arbre d'Huffman, par appel à la fonction coding_table_from_huffman_tree_recursive.
/// @param tree Arbre d'Huffman correspondant au fichier à compresser.
/// @return La table de codage correspondant au fichier à compresser.
CodingTable coding_table_from_huffman_tree(HuffmanTree tree)
{
    CodingTable table;
    BinaryCode code;

    table = coding_table_create();
    code = binary_code_create();
    coding_table_from_huffman_tree_recursive(tree, &table, &code);
    return table;
}

/// @brief Fonction écrivant l'en-tête du fichier compressé,
/// @details L'en-tête contient l'identifiant "HUFF" et les statistiques du fichier à compresser.
/// @param destination Le fichier compressé.
/// @param statistics Les statistiques du fichier à compresser.
/// @return Le résultat de la compression.
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

/// @brief Fonction qui lit les octets du fichier à compresser et écrit les code binaires correspondants dans le fichier compressé.
/// @param source Le fchier à compresser.
/// @param destination Le fichier compressé.
/// @param table La table de codage donnant l'équivalence octet / code binaire.
/// @return Le résultat de la compression.
CompressResult compress_source_bytes(FILE *source, FILE *destination, CodingTable table, FileSize fileSize)
{
    rewind(source);

    unsigned int i = 0; // Compteur de bits
    Byte inputByte = byte_create(0);
    Byte outputByte = byte_create(0);

    FileSize compressedBytes = 0;

    ProgressBar progressBar = progress_bar_create(fileSize, "Compressing");

    while (fread(&inputByte, sizeof(inputByte), 1, source) == 1) // Tant que l'on a pas atteint la fin du fichier
    {
        compressedBytes++;
        BinaryCode binaryCode = coding_table_get_value(&table, inputByte); // Cherche dans la CT son équivalence en BC

        for (unsigned int j = 0; j < binary_code_get_length(&binaryCode); j++)
        {
            byte_set_bit(&outputByte, i, binary_code_get_bit(&binaryCode, j)); // On accède à chaque bit d'un code binaire dans un octet
            i++;

            if (i >= 8) // Si on a accumulé 8 bits ou qu'on est à la fin du fichier.
            {
                if (fwrite(&outputByte, sizeof(outputByte), 1, destination) != 1) // Et on écrit sa compression dans le fichier destination
                    return COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;

                outputByte = byte_create(0);
                i = 0;
            }
        }
        progress_bar_update(&progressBar, compressedBytes);
    }
    if (ferror(source))
        return COMPRESS_RESULT_ERROR_FAILED_TO_READ_INPUT_FILE;

    if (i > 0 && fwrite(&outputByte, sizeof(outputByte), 1, destination) != 1) // Si on a des bits en attente, on les écrit
        return COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;
    return COMPRESS_RESULT_OK;
}

// - - Fonctions publiques

/// @brief Fonction principale pour compresser un fichier.
/// @param input Fichier non-compressé
/// @param output Fichier compressé
/// @return Résultat de la compression
CompressResult compress(FILE *input, FILE *output)
{
    CompressResult result = COMPRESS_RESULT_OK;
    // - Calcul des statistiques
    Statistics statistics;
    if (!statistics_compute_from_file(statistics, input))
        return COMPRESS_RESULT_ERROR_FAILED_TO_READ_INPUT_FILE;

    HuffmanTree huffmanTree;
    CodingTable codingTable;
    // Vérifie si le fichier n'est pas vide avant ou ne contient qu'un seul octet avant de créer l'arbre de Huffman et la table de codage (risque d'avoir des pointeurs nuls)
    if (statistics_get_total_count(statistics) != 0 && !statistics_is_unique(statistics)) 
    {
        // - Création de l'arbre de Huffman
        huffmanTree = huffman_tree_from_statistic(statistics);
        // - Création de la table de codage
        codingTable = coding_table_from_huffman_tree(huffmanTree);
        huffman_tree_delete(huffmanTree); // On libère la mémoire de l'arbre de Huffman
    }
    // - Écriture de l'en-tête
    result = write_header(output, statistics);
    // Si il y a une erreur, ou que le fichier est vide ou ne contient qu'un seul octet, on arrête la compression ici
    if (result != COMPRESS_RESULT_OK || statistics_get_total_count(statistics) == 0 || statistics_is_unique(statistics))
        return result;
    // - Compression des données
    return compress_source_bytes(input, output, codingTable, statistics_get_total_count(statistics));
}

/// @brief Fonction pour transcrire un résultat de compression en chaîne de caractères.
/// @param error Résultat de la décompression
/// @param buffer Chaîne de caractères résultante
/// @param bufferSize Taille de la chaîne de caractères résultante
/// @return Résultat de la compression
void compress_error_to_string(CompressResult error, char *buffer, size_t bufferSize)
{
    switch (error)
    {
    case COMPRESS_RESULT_OK:
        strncpy(buffer, "No error", bufferSize);
        break;
    case COMPRESS_RESULT_ERROR_FAILED_TO_READ_INPUT_FILE:
        strncpy(buffer, "File error", bufferSize);
        break;
    case COMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE:
        strncpy(buffer, "Premature end of file", bufferSize);
        break;
    case COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE:
        strncpy(buffer, "Failed to write output file", bufferSize);
        break;
    default:
        strncpy(buffer, "Unknown error", bufferSize);
        break;
    }
}