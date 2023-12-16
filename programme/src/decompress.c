#include "decompress.h"

#include <string.h>

bool is_huffman_compressed_file(FILE* input) {
    char identifier[4];
    if (fread(identifier, sizeof(char), sizeof(identifier), input) != 4) {
        return false;
    }

    if (strncmp(identifier, "HUFF", sizeof(identifier)) != 0) {
        return false;
    }

}

DecompressError read_header(FILE* input, size_t* size) {
    if (!is_huffman_compressed_file(input)) {
        return DECOMPRESS_ERROR_INVALID_HEADER;
    }

    if (fread(size, sizeof(size_t), 1, input) != 1) {
        return DECOMPRESS_FILE_ERROR;
    }

    for (size_t i = 0; i < 256; ++i) {
        size_t frequency;
        if (fread(&frequency, sizeof(size_t), 1, input) != 1) {
            return DECOMPRESS_FILE_ERROR;
        }
    }

}

DecompressError decompress(FILE *input, FILE *output) {


}

DecompressError decompress_error_to_string(DecompressError error, char *buffer, size_t buffer_size) {
    switch (error) {
        case DECOMPRESS_ERROR_OK:
            strncpy(buffer, "No error", buffer_size);
            break;
        case DECOMPRESS_ERROR_INVALID_HEADER:
            strncpy(buffer, "Invalid header", buffer_size);
            break;
        default:
            strncpy(buffer, "Unknown error", buffer_size);
            break;
    }
    return error;
}