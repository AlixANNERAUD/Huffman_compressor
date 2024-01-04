#include "compress.h"

#include "statistics.h"
#include "huffmanTree.h"
#include "statistics.h"
#include "codingTable.h"
#include "binaryCode.h"

#include <string.h>

// - Définitions

// - - Fonctions privées

void compute_statistics(Statistics* stat, FILE *input)
{
    Byte byte;
    statistics_initialize(*stat);
    fseek(input,0,SEEK_SET); 
    while (feof(input) == 0)
    {
        fread(&byte,sizeof(byte),1,input);
        statistics_increase_count(*stat, byte);
    }
}

void coding_table_from_huffman_tree_recursive(HuffmanTree tree, CodingTable* table, BinaryCode* current_code)
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

void write_header (FILE destination, Statistics stat, FileSize size)
{
    fprintf(&destination, "HUFF");                              // Identifiant d'un fichier compressé
    fprintf(&destination, "%llu", sizeof(*stat) + sizeof(size) + sizeof("HUFF") - 1 + size);    // Taille total du fichier
    fprintf(&destination, "%lu", sizeof(*stat) + sizeof(size) + sizeof("HUFF") - 1);            // Taille de l'entête
}

CompressResult compress_source_bytes (FILE source, FILE* destination, CodingTable table)
{
    BinaryCode bc;
    Byte byte = '\0';
    fseek(&source, 0, 0);   // Set la position à 0 (0) depuis le début du fichier (0, seek_set)
    while (feof(&source) == 0){                                 // Tant que l'on a pas atteint la fin du fichier
        fread(&byte, sizeof(byte), 1, &source);                 // On lit le byte courant
        bc = coding_table_get_value(&table, byte);              // Cherche dans la CT son équivalence en BC
        if (fwrite(&bc, sizeof(bc), 1, destination) != 1)       // Et on écrit sa compression dans le fichier destination
            return COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE;                
    }

    return COMPRESS_RESULT_OK;
} 

FileSize size_of_file(FILE* f)
{
    fseek(f,0,SEEK_SET); 
    FileSize size = 0;
    while (feof(f) == 0){           // Tant que l'on a pas atteint la fin du fichier
        fseek(f,1,SEEK_CUR);        // On avance d'un et on augmente la taille d'un
        size++;
    }
    return size;
}
// - - Fonctions publiques

CompressResult compress(FILE *input, FILE *output) 
{
    // Préconditions
    assert(input != NULL);
    assert(output != NULL);

    if (ferror(input) || ferror(output))
        return COMPRESS_RESULT_ERROR_FILE;

    if (feof(input))
        return COMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE;

    CompressResult result = COMPRESS_RESULT_OK;
    FileSize size;
    Statistics stat;
    HuffmanTree ht;
    CodingTable ct;
    statistics_initialize(stat);
    compute_statistics(&stat, input);
    ht = *huffman_tree_from_statistic(&stat);

    assert(ht != NULL);

    ct = coding_table_from_huffman_tree(ht);

    result = compress_source_bytes(*input, output, ct);
    size = size_of_file(output);
    write_header(*output, stat, size);

    return result;
}