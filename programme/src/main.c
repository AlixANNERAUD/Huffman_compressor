#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++) {
        printf("Argument %d : %s\n", i, argv[i]);
    }

    if (getcwd(NULL, 0) != NULL) {
        printf("Répertoire courant : %s\n", getcwd(NULL, 0));
    } else {
        printf("Erreur lors de la récupération du répertoire courant\n");
    }

    return EXIT_SUCCESS;
}