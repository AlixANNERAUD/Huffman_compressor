// - Dépendances
// - - Librairie standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
// - - Librairie système
#include <unistd.h>
// - - Local
#include "compress.h"
#include "decompress.h"

/// @brief Fonction qui affiche un message d'erreur sur la sortie d'erreur standard
/// @param format Format du message
/// @param  ... Arguments du message
void print_error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

/// @brief Fonction qui vérifie si une chaîne de caractères se termine par une autre
/// @param string Chaîne de caractères à vérifier
/// @param suffix Chaîne de caractères à chercher
/// @return `true` si `string` se termine par `suffix`, `false` sinon
bool ends_with(const char *string, const char *suffix)
{
    size_t strLength = strlen(string);
    size_t suffixLength = strlen(suffix);
    if (strLength < suffixLength)
        return false;
    else
        return strncmp(string + strLength - suffixLength, suffix, suffixLength) == 0;
}

/// @brief Fonction qui lit les arguments passés au programme
/// @param argc Nombre d'arguments
/// @param argv Arguments
/// @param mode Résultat de la lecture du mode
/// @param intput_file_path Résultat de la lecture du chemin du fichier d'entrée
/// @return `true` si les arguments ont bien été lus, `false` sinon
bool read_arguments(int argc, const char *argv[], char *mode, const char **intput_file_path)
{
    // - On vérifie le nombre d'arguments
    if (argc != 3)
    {
        print_error("Invalid number of arguments. Expected 2, got %d\n", argc - 1);
        return false;
    }
    // - On récupère et vérifie la commande
    *mode = *argv[1];

    if (*mode != 'c' && *mode != 'd')
    {
        print_error("Invalid compression mode. Expected c or d, got %s\n", mode);
        return false;
    }
    // - On récupère le nom du fichier d'entrée
    *intput_file_path = argv[2];

    return true;
}

/// @brief Fonction qui ouvre les fichiers en fonction du mode
/// @param mode Mode
/// @param input_file Fichier d'entrée résultant
/// @param output_file Fichier de sortie résultant
/// @return `true` si les fichiers ont bien été ouverts, `false` sinon
bool open_files(char mode, const char *input_file_path, FILE **input_file, FILE **output_file)
{
    // - Dans le cas d'une décompression, on vérifie que le fichier d'entrée est bien un fichier .huff
    if (mode == 'd' && !ends_with(input_file_path, ".huff"))
    {
        print_error("Invalid input file. Expected a .huff file, got : %s\n", input_file_path);
        return false;
    }
    *input_file = fopen(input_file_path, "r"); // On ouvre le fichier d'entrée en lecture
    // - On vérifie que le fichier a bien été ouvert
    if (*input_file == NULL || ferror(*input_file))
    {
        print_error("Error while opening input file.\n");
        return false;
    }
    rewind(*input_file); // On remet le curseur au début du fichier d'entrée

    // - Création du nom du fichier de sortie
    char *output_file_path = malloc(strlen(input_file_path) + 6); // +6 pour le ".huff\0" (pas forcément nécessaire dans le cas de la décompression, mais plus simple)
    switch (mode)
    {
    case 'c':
        strcpy(output_file_path, input_file_path); // On copie le nom du fichier d'entrée
        strcat(output_file_path, ".huff");         // On ajoute l'extension
        break;
    case 'd':
        strncpy(output_file_path, input_file_path, strlen(input_file_path) - 5); // On enlève les 5 derniers caractères (".huff")
        break;
    default:
        return false;
    }
    *output_file = fopen(output_file_path, "w+"); // On ouvre le fichier de sortie en écriture
    free(output_file_path);                       // On libère la mémoire allouée pour le nom du fichier de sortie
    // - On vérifie que le fichier a bien été ouvert
    if (*output_file == NULL || ferror(*output_file))
    {
        print_error("Error while opening output file.\n");
        return false;
    }
    return true;
}

int main(int argc, const char *argv[])
{
    // - Lecture et vérification des arguments
    char mode = '\0';
    const char *input_file_path;
    if (!read_arguments(argc, argv, &mode, &input_file_path))
        return EXIT_FAILURE;
    // - Ouverture des fichiers
    FILE *inputFile;
    FILE *outputFile;
    if (!open_files(mode, input_file_path, &inputFile, &outputFile))
        return EXIT_FAILURE;
    // - Compression / décompression
    if (mode == 'c')
    {
        // - Compression
        printf("Compressing ...\n");
        clock_t start = clock();
        CompressResult compressResult = compress(inputFile, outputFile);
        clock_t end = clock();
        // - Affichage du résultat
        if (compressResult != COMPRESS_RESULT_OK)
        {
            char errorBuffer[1024];
            FileSize buffer_size = sizeof(errorBuffer);
            compress_error_to_string(compressResult, errorBuffer, buffer_size);
            print_error("Error while compressing file: %s\n.", errorBuffer);
        }
        else
            printf("File compressed successfully in %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    else if (mode == 'd')
    {
        // - Décompression
        printf("Decompressing ...\n");
        clock_t start = clock();
        DecompressResult decompressResult = decompress(inputFile, outputFile);
        clock_t end = clock();
        // - Affichage du résultat
        if (decompressResult != DECOMPRESS_RESULT_OK)
        {
            char errorBuffer[1024];
            FileSize buffer_size = sizeof(errorBuffer);
            decompress_error_to_string(decompressResult, errorBuffer, buffer_size);
            print_error("Error while decompressing file: %s\n.", errorBuffer);
            
        }
        else
            printf("File decompressed successfully in %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    // - Fermeture des fichiers
    fclose(inputFile);
    fclose(outputFile);
    return EXIT_SUCCESS;
}
