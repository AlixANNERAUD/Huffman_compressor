#pragma once

typedef Bit Byte[8];

Byte byte_byte(unsigned int natural);

unsigned int byte_byte_to_natural(Byte byte);

void byte_set_bit(Byte* byte, unsigned int position, Bit bit);

Bit byte_get_bit(Byte byte, unsigned int position);