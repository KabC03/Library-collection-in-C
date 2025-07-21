#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


#define TYPE float

typedef struct LookupTable {
    TYPE *table;

    TYPE xStart;
    TYPE xStep;
} LookupTable;


/*
    The set:
        x = [0.1, 0.3, 0.5, 0.9, 1,1];
        y = [1, 3, 2, 4, 5];

    Is represented as:
        table = [1, 3, 2, 4, 5];
        xStart = 0.1;
        xStep = 0.2;
*/

void lookup_table_create(LookupTable *table, TYPE *newTable, TYPE newXStart, TYPE newXStep);
TYPE lookup_table_lookup(LookupTable *table, TYPE value);


#endif
