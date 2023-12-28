#include "statistics.h"

#include <string.h> // memcpy

Statistics statistics_create(){
    Statistics res;
    return res;
}

unsigned int statistics_get_count(Statistics stat, int e){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->lesElements[i])){
        i=i+1;
    }
    assert(e != stat->lesElements[i]);
    return stat->nbOccurrence[i];
}

void statistics_set_count(Statistics* stat, int e, unsigned int n){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->lesElements[i])){
        i=i+1;
    }
    assert(e != stat->lesElements[i]);
    stat->nbOccurrence[i] = n;
}

void statistics_increase_count(Statistics* stat, int e){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e == stat->lesElements[i])){
        i=i+1;
    }
    assert(e != stat->lesElements[i]);
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

 