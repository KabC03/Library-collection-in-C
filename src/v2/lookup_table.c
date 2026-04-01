#include "lookup_table.h"



/**
 * @brief :: Lookup a value in a table by value
 *
 * @param :: *table :: Table to instantiate
 * @param :: *newTable :: Table of y values
 * @param :: *newXStart :: Starting x value
 * @param :: newXStep :: Step x value
 *
 * @return :: TYPE :: Value
 */
void lookup_table_create(LookupTable *table, TYPE *newTable, TYPE newXStart, TYPE newXStep) {
    
    table->table = newTable;
    
    table->xStart = newXStart;
    table->xStep = newXStep;    

    return;
}


/**
 * @brief :: Lookup a value in a table by value
 *
 * @param :: *table :: Table to lookup in
 * @param :: *value :: Value to lookup
 *
 * @return :: TYPE :: Value
 */
TYPE lookup_table_lookup(LookupTable *table, TYPE value) {
    
    TYPE start = table->xStart;
    TYPE step = table->xStep;

    size_t index = (value - start) / step; //Could use round - but omit for speed
    TYPE ret = table->table[index];

    return ret;
}





