
//23 September 2024
#ifndef ARBITRARY_LENGTH_H 
#define ARBITRARY_LENGTH_H

#include "vector.h"
#include <stdio.h>
#include <math.h>

#define SIZE_T_DIGITS (int)log10(SIZE_MAX)
#define SIZE_T_MAX_PART pow(10, SIZE_T_DIGITS)


typedef struct ArbitraryInteger {

    //char sign; //Do this later
    Vector magnitude;

} ArbitraryInteger;





void arbitrary_integer_print(ArbitraryInteger *arg);
bool arbitrary_integer_init(ArbitraryInteger *arg);
void arbitrary_integer_destroy(ArbitraryInteger *arg);
bool arbitrary_integer_set(ArbitraryInteger *arg, size_t *data, size_t numel);
bool arbitrary_integer_add(ArbitraryInteger *arg1, ArbitraryInteger *arg2);

#endif 



      
      
      
      