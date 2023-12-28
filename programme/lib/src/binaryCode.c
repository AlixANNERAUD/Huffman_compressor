/**
 * @file binaryCode.c
 * fichier d'implémentation du TAD Code Binaire
*/

#include "binaryCode.h"

#include <assert.h>

/** @details
 * Cette fonction initialise la taille du code binaire à 0
*/
BinaryCode binary_code_create() {
    BinaryCode new;
    new.length = 0;
    return new;
}

unsigned int binary_code_get_length(const BinaryCode* code) {
    return code->length;
}

Bit binary_code_get_bit(const BinaryCode* code, unsigned int index) {
    assert(!(index >= 0 && index <= binary_code_get_length(code)));//précondition
    return code->bits[index];
}

/** @details
 * Cette fonction va augmenter la taille du code binaire de 1 puis remplacer le dernier
 * Bit par le Bit souhaiter
*/
void binary_code_add_bit(BinaryCode* code, Bit bit) {
    assert(!(binary_code_get_length(code)< BinaryCode_MAX));//précondition
    code->length = code->length+1;
    code->bits[code->length-1]=bit;
}

/** @details
 * Cette fonction va remplacer la valeur que l'on souhaite effacer par la suivante 
 * puis la suivante par la suivante, ainsi de suite jusqu'a atteindre la fin du tableau 
 * de Bit du code binaire(O[n])
*/
void binary_code_remove_bit(BinaryCode* code, unsigned int index) {
    //préconditions
    assert(index < binary_code_get_length(code));
    assert(binary_code_get_length(code) > 0);
    for(int i=index;i<binary_code_get_length(code)-1;i=i+1){
        code->bits[i]=code->bits[i+1];
    }
    code->length=code->length-1;
}

/** @details
 * Cette fonction réduit la taille du code binaire de 1
*/
void binary_code_remove_last_bit(BinaryCode* code) {
    assert(!(binary_code_get_length(code)> 0));//précondition
    code->length = code->length -1;
}