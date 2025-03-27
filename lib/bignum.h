#ifndef BIGNUM_H
#define BIGNUM_H
#include <ctype.h>
#include "vector.h"
#include "strings.h"


typedef struct Bignum {

    char sign;
    String data;

} Bignum;


void bignum_print(Bignum *bignum);
void bignum_init(Bignum *bignum);
bool bignum_from_string(Bignum *bignum, char *string);
bool bignum_add(Bignum *dest, Bignum *src1, Bignum *src2);





#endif



