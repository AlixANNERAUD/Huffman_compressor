#include "compress.h"
#include "statistics.h"
#include "huffmanTree.h"


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
