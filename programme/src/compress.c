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
