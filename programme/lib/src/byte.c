#include "byte.h"
#include <assert.h>

Byte byte_create(unsigned int natural){
    // Préconditions
    assert(natural <= 0xFF);

    Byte res = natural;

    return res;
}

unsigned int byte_to_natural(Byte byte){
    
    unsigned int res = byte;

    return res;
}

void byte_set_bit(Byte* byte, unsigned int position, Bit bit) {
    // Préconditions
    assert(position <= 7);

    Byte temp = byte;
    if (bit == BIT_0)
        temp &= ~(1 << position); 
    // &= AND, ~ NOT, décaler à gauche puis fixer le bit 0 à la position donnée
    else 
        temp |= (1 << position); 
    // |= OR, décaler à gauche puis fixer le bit 1 à la position donnée
    *byte = temp;
}

Bit byte_get_bit(Byte byte, unsigned int position){
    // Préconditions
    assert(position <= 7);

    Bit res;
    if ((byte >> position)&1 == 1) 
    // décaler à droite puis comparer avec 1 (en utilisant AND) donne le bit à la position donnée
        res = BIT_1;
    else
        res = BIT_0;
    return res;
}
