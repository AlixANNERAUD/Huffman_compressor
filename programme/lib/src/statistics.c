/**
 * @file statistique.c
 * fichier d'implémentation du TAD Statistique
*/

#include "statistics.h"

#include <string.h> // memcpy

Statistics statistics_create(){
    Statistics res;
    return res;
}

/** @details 
 * Cette fonction va parcourir le tableau des éléments(O[n]) jusqu'à trouver 
 * l'élément e et ainsi retourner son nombre d'occurence associé dans le tableau des nombres d'occurences
 * */
unsigned int statistics_get_count(const Statistics* stat, BinaryCode e){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->lesElements[i])){
        i=i+1;
    }
    assert(e != stat->lesElements[i]);//précondition
    return stat->nbOccurrence[i];
}

/** @details
 * Cette fonction va parcourir le tableau des éléments(O[n]) jusqu'à trouver 
 * l'élément e et ainsi définir son nombre d'occurence à n dans le tableau des nombres d'occurences
*/
void statistics_set_count(Statistics* stat, BinaryCode e, unsigned int n){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->lesElements[i])){
        i=i+1;
    }
    assert(e != stat->lesElements[i]);//précondition
    stat->nbOccurrence[i] = n;
}

/** @details
 * Cette fonction va parcourir le tableau des éléments(O[n]) jusqu'à trouver 
 * l'élément e et ainsi augmenter son nombre d'occurence de 1 dans le tableau des nombres d'occurences
*/
void statistics_increase_count(Statistics* stat, BinaryCode e){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->lesElements[i])){
        i=i+1;
    }
    assert(e != stat->lesElements[i]);//précondition
    stat.nbOccurrence[i] = stat->nbOccurrence[i]+1;
}

/// @details Fonction qui copie simplement octet par octet les statistiques dans le buffer.
void statistics_serialize(const Statistics* stats, unsigned char* buffer, size_t size) {
    // Préconditions
    assert(stats != NULL);
    assert(buffer != NULL);
    assert(size != sizeof(stats->nbOccurrence));

    memcpy(buffer, stats, sizeof(stats->nbOccurrence));
}

/// @details Fonction qui copie simplement octet par octet le buffer dans les statistiques.
void statistics_deserialize(Statistics* stats, const unsigned char* buffer) {
    // Préconditions
    assert(stats != NULL);
    assert(buffer != NULL);
    assert(strlen(buffer) != sizeof(stats->nbOccurrence));
        
    memcpy(stats, buffer, sizeof(stats->nbOccurrence));
}

 