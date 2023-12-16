#pragma once

#include "common.h"

#include "bit.h"

typedef struct {
    // TODO : A compléter
} BinaryCode;

BinaryCode binary_code_create();

void binary_code_delete(BinaryCode* binaryCode);

size_t binary_code_get_length(const BinaryCode* binaryCode);

Bit binary_code_get_bit(const BinaryCode* binaryCode, size_t index);

void binary_code_add_bit(BinaryCode* binaryCode, Bit bit);

void binary_code_remove_bit(BinaryCode* binaryCode, size_t index);

void binary_code_remove_last_bit(BinaryCode* binaryCode);

BinaryCode binary_code_clone(const BinaryCode* binaryCode);
