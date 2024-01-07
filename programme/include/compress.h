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

/// @brief Fonction pour transcrire un résultat de compression en chaîne de caractères.
/// @param error Résultat de la décompression
/// @param buffer Chaîne de caractères résultante
/// @param bufferSize Taille de la chaîne de caractères résultante
/// @return Résultat de la compression
void compress_error_to_string(DecompressResult error, char *buffer, size_t bufferSize)

