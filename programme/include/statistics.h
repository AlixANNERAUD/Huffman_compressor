#ifndef STATISTICS_H_DEFINED
#define STATISTICS_H_DEFINED

#define MAX 256

typedef struct
{
    int lesElements[MAX]; // type huffmantree
    unsigned int nbOccurrence[MAX];
} Statistics;

Statistics statistics();

unsigned int getCount(Statistics stat, int e);

Statistics setCount(Statistics stat, int e, unsigned int n);

Statistics increaseCount(Statistics stat, int e);

#endif // STATISTICS_H_DEFINED