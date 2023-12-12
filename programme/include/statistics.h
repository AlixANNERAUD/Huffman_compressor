#ifndef STATISTICS_H_DEFINED
#define STATISTICS_H_DEFINED

#define Statistics_MAX 256

typedef struct
{
    int lesElements[Statistics_MAX]; // type huffmantree
    unsigned int nbOccurrence[Statistics_MAX];
} Statistics;

Statistics Statistics_statistics();

unsigned int Statistics_getCount(Statistics stat, int e);

Statistics Statistics_setCount(Statistics stat, int e, unsigned int n);

Statistics Statistics_increaseCount(Statistics stat, int e);

#endif // STATISTICS_H_DEFINED