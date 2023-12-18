#pragma once

#include "bit.h"

typedef unsigned char Byte;

Byte byte_create(unsigned int natural);

unsigned int byte_to_natural(Byte byte);

void byte_set_bit(Byte* byte, unsigned int position, Bit bit);

Bit byte_get_bit(Byte byte, unsigned int position);