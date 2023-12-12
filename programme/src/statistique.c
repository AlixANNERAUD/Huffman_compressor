#include "statistics.h"

Statistics Statistics_statistics(){
    Statistics res;
    res.lesElements[Statistics_MAX];
    res.nbOccurrence[Statistics_MAX];
    return res;
}

unsigned int Statistics_getCount(Statistics stat, int e){
    int i = 1;
    while(i<=Statistics_MAX-1 && not(e = stat.lesElements[i])){
        i=i+1;
    }
    return stat.nbOccurrence[i];
}

Statistics Statistics_setCount(Statistics stat, int e, unsigned int n){
    int i;
    while(i<=Statistics_MAX-1 && not(e = stat.lesElements[i])){
        i=i+1;
    }
    stat.nbOccurrence[i] = n;
    return stat;
}

Statistics Statistics_increaseCount(Statistics stat, int e){
    int i;
    while(i<=Statistics_MAX-1 && not(e = stat.lesElements[i])){
        i=i+1;
    }
    stat.nbOccurrence[i] = stat.nbOccurrence[i]+1;
    return stat;
}