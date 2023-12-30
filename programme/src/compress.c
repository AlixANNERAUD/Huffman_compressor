#include "compress.h"
#include "statistics.h"
#include "huffmanTree.h"
#include "codingTable.h"


bool compress(FILE *input, FILE *output) {
    //fopen(&input, "rb");
    //fopen(&output, "wb");
    // TODO
    return false;
}

Statistics* compute_statistics(FILE *input){
    Byte byte;
    Statistics* stat;
    
    stat = NULL;
    statistics_initialize(*stat);
    fseek(input,0,SEEK_SET); 
    while (feof(input) == 0)
    {
        fread(&byte,sizeof(byte),1,input);
        statistics_increase_count(*stat, byte);
    }
    return stat;
}

void coding_table_from_huffman_tree_recursive(HuffmanTree tree, CodingTable* table, BinaryCode* current_code){
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

CodingTable coding_table_from_huffman_tree(HuffmanTree tree){
    CodingTable table;
    BinaryCode code;

    table = coding_table_create();
    code = binary_code_create();
    coding_table_from_huffman_tree_recursive(tree, &table, &code);
    return table;
}
// Pour être franc je comprends pas pourquoi on utilise la variable byte ici. 
// Bah franchement, je sais pas non plus... Elle a sauté

void write_header (FILE destination, Statistics stat, FileSize size){
    fprintf(&destination, "HUFF");
    fprintf(&destination, "%llu", size);
    fprintf(&destination, "%lu", sizeof(*stat) + sizeof(size) + sizeof("HUFF") - 1);
}

/* void compress_source_bytes (FILE source, FILE* destination, CodingTable table){
    BinaryCode bc;
    Byte b = '\0';
    char c;
    fseek(&source, 0, 0);   // Set la position à 0 (0) depuis le début du fichier (0, seek_set)
    while ((c = getchar()) != EOF){
        fgets(b, 8, &source); // Comment lire un byte, en lisant 8 caractères et.. jsp
        bc = coding_table_get_value(&table, b);
        fprintf(destination, "%bc", bc);    // Comment écrire un bc ? L'écrire bit par bit ? Si oui comment (pour écrire les bits 01001 et non la chaîne '01001' ?)
    }
} */
