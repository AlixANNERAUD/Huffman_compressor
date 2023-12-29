#include "compress.h"
#include "statistics.h"
#include "huffmanTree.h"
#include "codingTable.h"

bool compress(FILE *input, FILE *output) {
    // TODO
    return false;
}

Statistics compute_statistics(FILE *input){
    Byte byte;
    Statistics stat;
    
    stat = statistics_create();
    fseek(input,0,SEEK_SET); 
    while (feof(input) == 0)
    {
        fread(&byte,sizeof(byte),1,input);
        statistics_increase_count(&stat, byte);
    }
    return stat;
}

//La fonction huffman_tree_from_statistic correspond à buildHuffmanTree dans le rapport
//Mais il me semble qu'elle n'est pas encore finie dans huffmanTree.c

CodingTable coding_table_from_huffman_tree(HuffmanTree tree){
    CodingTable table;
    BinaryCode code;
    Byte byte = 0;

    table = coding_table_create();
    code = binary_code_create();
    coding_table_from_huffman_tree_recursive(tree, &table, &code, byte);
    return table;
}
// Pour être franc je comprends pas pourquoi on utilise la variable byte ici.

void coding_table_from_huffman_tree_recursive(HuffmanTree tree, CodingTable* table, BinaryCode* current_code, Byte byte){
    if (huffman_tree_is_leaf(tree))
        coding_table_add(&table,huffman_tree_get_value(tree),current_code);
    else
    {
        binary_code_add_bit(&current_code, BIT_0);
        coding_table_from_huffman_tree_recursive(huffman_tree_get_left_child(tree), &table, &current_code, byte);
        binary_code_remove_last_bit(&current_code);
        binary_code_add_bit(&current_code, BIT_1);
        coding_table_from_huffman_tree_recursive(huffman_tree_get_right_child(tree), &table, &current_code, byte);
        binary_code_remove_last_bit(&current_code);
    }
}
// J'ai pas très bien compris cet algo