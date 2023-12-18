#include "binaryCode.h"

#include <assert.h>

BinaryCode binary_code_create() {
    BinaryCode new;
    new.length = 0;
    return new;
}

void binary_code_delete(BinaryCode* code) {
    free(code);
}

unsigned int binary_code_get_length(const BinaryCode* code) {
    return code->length;
}

Bit binary_code_get_bit(const BinaryCode* code, unsigned int index) {
    if(index >= 0 && index <= binary_code_get_length(code)){
        return code->bits[index];
    }
    else{
        printf("error return first value");
        return code->bits[0];
    }
}

void binary_code_add_bit(BinaryCode* code, Bit bit) {
    if(binary_code_get_length(code)< BinaryCode_MAX){
        code->length = code->length+1;
    }
    else{
        printf("error length too high");
    }
}

void binary_code_remove_bit(BinaryCode* code, unsigned int index) {//ps pas dutout le bon code CD pas bonne
    if(index >= 0 && index <= binary_code_get_length(code)){
        if(binary_code_get_length(code) > 0){
            code->length = code->length -1;
        }
    }
    else{
        printf("index out of range");
    }
}

void binary_code_remove_last_bit(BinaryCode* code) {
    if(binary_code_get_length(code)< BinaryCode_MAX){
        if(binary_code_get_length(code) > 0){
            code->length = code->length -1;
        }
    }
    else{
        printf("index out of range");
    }
}

BinaryCode binary_code_clone(const BinaryCode* code) {
    // TODO : Implémenter la fonction
}

