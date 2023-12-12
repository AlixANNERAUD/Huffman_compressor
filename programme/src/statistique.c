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