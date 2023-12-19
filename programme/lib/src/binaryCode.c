#include "binaryCode.h"

#include <assert.h>

BinaryCode binary_code_create() {
    BinaryCode new;
    new.length = 0;
    return new;
}

unsigned int binary_code_get_length(const BinaryCode* code) {
    return code->length;
}

Bit binary_code_get_bit(const BinaryCode* code, unsigned int index) {
    assert(!(index >= 0 && index <= binary_code_get_length(code)));
    return code->bits[index];
}

void binary_code_add_bit(BinaryCode* code, Bit bit) {
    assert(!(binary_code_get_length(code)< BinaryCode_MAX));
    code->length = code->length+1;
    code->bits[code->length-1]=bit;
}

void binary_code_remove_bit(BinaryCode* code, unsigned int index) {
    assert(index < binary_code_get_length(code));
    assert(binary_code_get_length(code) > 0);
    for(int i=index;i<binary_code_get_length(code)-1;i=i+1){
        code->bits[i]=code->bits[i+1];
    }
    code->length=code->length-1;
}

void binary_code_remove_last_bit(BinaryCode* code) {
    assert(!(binary_code_get_length(code)> 0));
    code->length = code->length -1;
}