#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include <compress.h>
#include <decompress.h>

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++) {
        printf("Argument %d : %s\n", i, argv[i]);
    }

    if (argc != 3) {
        printf("Mauvais nombre d'arguments renseigné\n");
        return 1;
    }
    if (getcwd(NULL, 0) != NULL) {
        printf("Répertoire courant : %s\n", getcwd(NULL, 0));
    } else {
        printf("Erreur lors de la récupération du répertoire courant\n");
        return 1;
    }

    char * mode = argv[1];
    char * filename = argv[2];

    FILE * input;
    FILE * output; 

    if (*mode == 'c'){
        CompressResult cr;
        input = fopen(filename, "rb");
        output = fopen(filename, "wb");
        cr = compress(input, output);
        /*
        char buffer[40];
        FileSize buffer_size = sizeof(buffer);
        compress_error_to_string(cr, buffer, buffer_size);
        printf("%s", buffer);
        */
        fclose(input);
        fclose(output);
    } else if (*mode == 'd'){
        DecompressResult dr;
        input = fopen(filename, "rb");
        output = fopen(filename, "wb");
        dr = decompress(input, output);
        char buffer[40];
        FileSize buffer_size = sizeof(buffer);
        decompress_error_to_string(dr, buffer, buffer_size);
        printf("%s", buffer);
        fclose(input);
        fclose(output);
    } else {
        printf("Le deuxième argument doit être c (compresser) ou d (décompresser). %s est un argument invalide.", mode);
        return 1;
    }
    return EXIT_SUCCESS;
}
