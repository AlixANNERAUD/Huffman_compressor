#include "statistics.h"

Statistics Statistics_statistics(){
    Statistics res;
    return res;
}

unsigned int Statistics_getCount(Statistics stat, int e){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e = stat.lesElements[i])){
        i=i+1;
    }
    return stat.nbOccurrence[i];
}

Statistics Statistics_setCount(Statistics stat, int e, unsigned int n){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e = stat.lesElements[i])){
        i=i+1;
    }
    stat.nbOccurrence[i] = n;
    return stat;
}

Statistics Statistics_increaseCount(Statistics stat, int e){
    int i = 0;
    while(i<=Statistics_MAX-1 && !(e = stat.lesElements[i])){
        i=i+1;
    }
    stat.nbOccurrence[i] = stat.nbOccurrence[i]+1;
    return stat;
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

 