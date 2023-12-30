/**
 * @file statistique.c
 * fichier d'implémentation du TAD Statistique
*/

#include "statistics.h"

#include <string.h> // memcpy

Statistics statistics_create(){
    Statistics res;
    for(int i=0; i<Statistics_MAX; i++){
        res.elements[i] = byte_create(i);
        res.count[i] = 0;
    }
    return res;
}

/** @details 
 * Cette fonction va parcourir le tableau des éléments(O[n]) jusqu'à trouver 
 * l'élément e et ainsi retourner son nombre d'occurence associé dans le tableau des nombres d'occurences
 * */
unsigned int statistics_get_count(const Statistics* stat, Byte e){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->elements[i])){
        i=i+1;
    }
    assert(e != stat->elements[i]);//précondition
    return stat->count[i];
}

/** @details
 * Cette fonction va parcourir le tableau des éléments(O[n]) jusqu'à trouver 
 * l'élément e et ainsi définir son nombre d'occurence à n dans le tableau des nombres d'occurences
*/
void statistics_set_count(Statistics* stat, Byte e, unsigned int n){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->elements[i])){
        i=i+1;
    }
    assert(e != stat->elements[i]);//précondition
    stat->count[i] = n;
}

/** @details
 * Cette fonction va parcourir le tableau des éléments(O[n]) jusqu'à trouver 
 * l'élément e et ainsi augmenter son nombre d'occurence de 1 dans le tableau des nombres d'occurences
*/
void statistics_increase_count(Statistics* stat, Byte e){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->elements[i])){
        i=i+1;
    }
    assert(e != stat->elements[i]);//précondition
    stat->count[i] = stat->count[i]+1;
}

/// @details Fonction qui copie simplement octet par octet les statistiques dans le buffer.
void statistics_serialize(const Statistics* stats, unsigned char* buffer, FileSize size) {
    // Préconditions
    assert(stats != NULL);
    assert(buffer != NULL);
    assert(size != sizeof(stats->count));

    memcpy(buffer, stats, sizeof(stats->count));
}

/// @details Fonction qui copie simplement octet par octet le buffer dans les statistiques.
void statistics_deserialize(Statistics* stats, const unsigned char* buffer) {
    // Préconditions
    assert(stats != NULL);
    assert(buffer != NULL);
    assert(strlen((const char *) buffer) != sizeof(stats->count));
        
    memcpy(stats, buffer, sizeof(stats->count));
}
