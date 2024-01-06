#pragma once

// - Bibliothèques

#include "common.h"
#include <stdio.h>

// - Déclarations

// -- Types

typedef enum {
    COMPRESS_RESULT_OK,
    COMPRESS_RESULT_ERROR_FILE,
    COMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE,
    COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE,
    COMPRESS_RESULT_ERROR_FAILED_TO_WRITE_HEADER,
    COMPRESS_RESULT_ERROR_FAILED_TO_READ_INPUT_FILE,
    //COMPRESS_RESULT_INCONSISTENT_DECOMPRESSED_FILE
} CompressResult;

/// @brief Fonction principale pour compresser un fichier.
/// @param input Fichier non-compressé
/// @param output Fichier compressé
/// @return Résultat de la compression
CompressResult compress(FILE *in, FILE *out);

