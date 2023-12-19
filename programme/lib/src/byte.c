#include "byte.h"
#include <assert.h>

Byte byte_create(unsigned int natural){
    assert(natural <= 0xFF);

    Byte res = natural;

    return res;
}

unsigned int byte_to_natural(Byte byte){
    
    unsigned int res=byte;

    return res;
}

void byte_set_bit(Byte* byte, unsigned int position, Bit bit) {
    assert(position <= 7);

    Byte temp = byte;
    if (bit == BIT_0)
        temp &= ~(1 << position); // and
    else 
        temp |= (1 << position); // or
    *byte = temp;
}

Bit byte_get_bit(Byte byte, unsigned int position){
    assert(position <=7);

    Bit res;
    if ((byte >> position)&1 == 1) // comparer(and) avec 1 donne le bit
        res = BIT_1;
    else
        res = BIT_0;
    return res;
}