#include "bignum.h"



/**
 * @brief :: Print a bignum
 *
 * @param :: *bignum :: Bignum to print
 * 
 * @return :: void
 */
void bignum_print(Bignum *bignum) {

    printf("%c%s\n", bignum->sign, strings_read(&(bignum->data)));
    
    return;
}



/**
 * @brief :: Initialise a bignum
 *
 * @param :: *bignum :: Bignum to initialise
 * 
 * @return :: void
 */
void bignum_init(Bignum *bignum) {

    strings_init(&(bignum->data));
    
    return;
}


/**
 * @brief :: Set the value of a bignum from a string in the form [+,-][number]
 *
 * @param :: *bignum :: Set a bignum from a string value
 * 
 * @return :: bool :: Indication of parsing success/failure
 */
bool bignum_from_string(Bignum *bignum, char *string) {

    switch(string[0]) {
        case '+': {
        } case '-': {
            bignum->sign = string[0];
            break;
        } default: {
            return false;
        }
    }
    strings_set(&(bignum->data), string + sizeof(char), strlen(string) - sizeof(char));
    return true;
}






/**
 * @brief :: Add two bignums to produce a result
 * 
 * @param :: *dest :: Destination number
 * @param :: *src1 :: First number
 * @param :: *src2 :: Second number
 * 
 * @return :: void
 */
bool bignum_add(Bignum *dest, Bignum *src1, Bignum *src2) {

    //Find shorter number
    //Loop over numbers and add digits
    //Maintain carry

    size_t loopStop = (strings_length(&(src1->data)) > strings_length(&(src2->data))) ? 
    strings_length(&(src2->data)) : strings_length(&(src1->data));

    int carry = 0;
    for(size_t i = 0; i < loopStop + carry / 10; i++) { //Keep going until there is no more carry

        int t1 = *(strings_read_index(&(src1->data), i)) - '0';
        int t2 = *(strings_read_index(&(src2->data), i)) - '0';

        int temp = (t1 + t2) + carry;

        strings_set_index(&(dest->data), temp + '0', i);

        carry = temp / 10; //Take advantage of integer truncation
    }



    return true;
}











