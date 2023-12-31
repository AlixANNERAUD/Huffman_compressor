#pragma once

// - Bibliothèques 

#include "common.h"
#include <stdio.h>

// - Déclarations

// - - Types

typedef enum {
    DECOMPRESS_RESULT_OK,
    DECOMPRESS_RESULT_ERROR_FILE,
    DECOMPRESS_RESULT_ERROR_PREMATURE_END_OF_FILE,
    DECOMPRESS_RESULT_ERROR_INVALID_HEADER,
    DECOMPRESS_RESULT_ERROR_FAILED_TO_WRITE_OUTPUT_FILE,
    DECOMPRESS_RESULT_FAILED_TO_CHECK_OUTPUT_FILE,
    DECOMPRESS_RESULT_INCONSISTENT_DECOMPRESSED_FILE
} DecompressResult;

// - - Fonctions

/// @brief Fonction principale pour décompresser un fichier compresser par compress.
/// @param input Fichier compressé
/// @param output Fichier décompressé
/// @return Résultat de la décompression
DecompressResult decompress(FILE* input, FILE* output);

/// @brief Fonction pour transcrire un résultat de décompression en chaîne de caractères.
/// @param error Résultat de la décompression
/// @param buffer Chaîne de caractères résultante
/// @param bufferSize Taille de la chaîne de caractères résultante
/// @return Résultat de la décompression
void decompress_error_to_string(DecompressResult error, char* buffer, size_t bufferSize);

