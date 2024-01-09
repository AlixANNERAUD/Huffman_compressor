// - Dépendances
// - - Librairie standard
#include <string.h> // strncmp
// - - Locales
#include "decompress.h"
#include "huffmanTree.h"
#include "statistics.h"
#include "binaryCode.h"
#include "progressBar.h"

// - Définitions

// - - Fonctions privées

/// @brief Fonction pour vérifier si un fichier est compressé par Huffman.
/// @details Cette fonction lit les 4 premiers octets du fichier et vérifie si ils correspondent à l'identifiant "HUFF".
/// @param input Fichier à vérifier
/// @return `true` si le fichier est compressé par Huffman, `false` sinon
bool is_huffman_compressed_file(FILE *input)
{
    char identifier[4];
    if (fread(identifier, sizeof(char), sizeof(identifier), input) != 4)
        return false;

    if (strncmp(identifier, "HUFF", sizeof(identifier)) != 0)
        return false;

    return true;
}

/// @brief Fonction pour lire l'en-tête d'un fichier compressé.
/// @param input Fichier compressé
/// @param statistics Statistiques résultant du fichier compressé (extraites de l'en-tête)
/// @return Résultat de la lecture de l'en-tête
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

/// @brief Fonction pour décompresser les données d'un fichier compressé.
/// @param input Fichier compressé ouvert en lecture
/// @param output Fichier décompressé ouvert en écriture
/// @param tree Arbre de Huffman utilisé pour la compression
/// @param fileSize Taille du fichier décompressé
/// @return DECOMPRESS_RESULT_OK si la décompression s'est bien passée, un autre résultat sinon
DecompressResult decompress_data(FILE *input, FILE *output, const HuffmanTree tree, FileSize fileSize)
{
    if (fileSize == 0)
        return DECOMPRESS_RESULT_OK;

    unsigned char i = 8;
    HuffmanTree currentTree = tree;
    Byte sourceByte = byte_create(0);
    FileSize decompressedBytes = 0;
    // - Progression
    ProgressBar progressBar = progress_bar_create(fileSize, "Decompressing");

    // - Tant qu'on a pas atteint la taille du fichier original
    while (decompressedBytes < fileSize)
    {
        // - Lecture d'un octet du fichier d'entrée si on a lu tous les bits de l'octet précédent
        if (i > 7)
        {
            unsigned char bitsRead;
            if (fread(&bitsRead, sizeof(bitsRead), 1, input) != 1 && ferror(input))
                return DECOMPRESS_RESULT_ERROR_FILE;
            sourceByte = byte_create(bitsRead); // Conversion d'un naturel non signé d'un octet en octet
            i = 0;
        }

        // - Si c'est une feuille, on écrit la valeur de l'octet dans le fichier de sortie
        if (huffman_tree_is_leaf(currentTree))
        {
            Byte destinationByte = huffman_tree_get_value(currentTree);          // On récupère la valeur de l'octet
            unsigned char naturalToWrite = byte_to_natural(destinationByte);     // Conversion d'un octet en naturel non signé d'un octet
            if (fwrite(&naturalToWrite, sizeof(naturalToWrite), 1, output) != 1) // Ecriture de l'octet dans le fichier de sortie
                return DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;
            decompressedBytes++; // On incrémente le nombre d'octets décompressés
            currentTree = tree;  // Retour à la racine
        }
        // - Sinon, on continue de parcourir l'arbre
        else
        {
            Bit bit = byte_get_bit(sourceByte, i); // On récupère le bit
            if (bit == BIT_0)
                currentTree = currentTree->leftChild;
            else
                currentTree = currentTree->rightChild;
            i++;
        }

        progress_bar_update(&progressBar, decompressedBytes); // Mise à jour de la barre de progression
    }
    return DECOMPRESS_RESULT_OK; // Si il n'y a pas eu de renvoi prématuré, c'est que tout s'est bien passé
}

/// @brief Fonction pour vérifier si les statistiques d'un fichier décompressé correspondent aux statistiques du fichier compressé.
/// @param output Fichier décompressé
/// @param inputStatistics Statistiques du fichier compressé
/// @return Résultat de la vérification
DecompressResult check_output_file(FILE *output, const Statistics inputStatistics)
{
    rewind(output); // On remet le curseur au début du fichier
    // - Calcul des statistiques du fichier décompressé
    Statistics outputStatistics;
    if (!statistics_compute_from_file(outputStatistics, output))
        return DECOMPRESS_RESULT_FAILED_TO_CHECK_OUTPUT_FILE;
    // - Comparaison des statistiques
    if (!statistics_are_equals(inputStatistics, outputStatistics))
        return DECOMPRESS_RESULT_INCONSISTENT_DECOMPRESSED_FILE;
    return DECOMPRESS_RESULT_OK;
}

// - - Fonctions publiques

DecompressResult decompress(FILE *input, FILE *output)
{
    DecompressResult result = DECOMPRESS_RESULT_OK;
    // - Lecture de l'en-tête
    Statistics statistics;
    statistics_initialize(statistics);
    result = read_header(input, statistics);
    if (result != DECOMPRESS_RESULT_OK)
        return result;
    // - Reconstruction de l'arbre de Huffman
    HuffmanTree tree = huffman_tree_from_statistic(statistics);
    // - Décompression des données
    result = decompress_data(input, output, tree, statistics_get_total_count(statistics));
    if (result != DECOMPRESS_RESULT_OK)
        return result;
    huffman_tree_delete(tree); // On nettoie l'arbre
    // - Vérification du fichier décompressé
    return check_output_file(output, statistics);
}

void decompress_error_to_string(DecompressResult error, char *buffer, size_t bufferSize)
{
    switch (error)
    {
    case DECOMPRESS_RESULT_OK:
        strncpy(buffer, "No error", bufferSize);
        break;
    case DECOMPRESS_RESULT_ERROR_FILE:
        strncpy(buffer, "File error", bufferSize);
        break;
    case DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE:
        strncpy(buffer, "Premature end of file", bufferSize);
        break;
    case DECOMPRESS_RESULT_ERROR_INVALID_HEADER:
        strncpy(buffer, "Invalid header", bufferSize);
        break;
    case DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE:
        strncpy(buffer, "Failed to write output file", bufferSize);
        break;
    case DECOMPRESS_RESULT_INCONSISTENT_DECOMPRESSED_FILE:
        strncpy(buffer, "Inconsistent decompressed file", bufferSize);
        break;
    default:
        strncpy(buffer, "Unknown error", bufferSize);
        break;
    }
}
