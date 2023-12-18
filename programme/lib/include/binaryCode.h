#pragma once

#include "common.h"

#include "bit.h"

#define BinaryCode_MAX 1000

typedef struct {
    Bit bits[BinaryCode_MAX]; 
    unsigned int length;
} BinaryCode;

BinaryCode binary_code_create();

void binary_code_delete(BinaryCode* binaryCode);

unsigned int binary_code_get_length(const BinaryCode* binaryCode);

Bit binary_code_get_bit(const BinaryCode* binaryCode, unsigned int index);

void binary_code_add_bit(BinaryCode* binaryCode, Bit bit);

void binary_code_remove_bit(BinaryCode* binaryCode, unsigned int index);

void binary_code_remove_last_bit(BinaryCode* binaryCode);

BinaryCode binary_code_clone(const BinaryCode* binaryCode);
