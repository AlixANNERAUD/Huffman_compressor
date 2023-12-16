#ifndef DECOMPRESS_H_INCLUDED
#define DECOMPRESS_H_INCLUDED

#include "common.h"
#include <stdio.h>

typedef enum {
    DECOMPRESS_ERROR_OK,
    DECOMPRESS_FILE_ERROR,
    DECOMPRESS_ERROR_INVALID_HEADER,

} DecompressError;

bool decompress(FILE* input, FILE* output);

void decompress_error_to_string(DecompressError error, char* buffer, size_t buffer_size);

#endif // DECOMPRESS_H_INCLUDED