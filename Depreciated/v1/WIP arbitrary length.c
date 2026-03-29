#include "arbitrary length.h"



/**
 * @brief :: Print an arbitrary length integer
 *
 * @param :: *arg :: Item to be printed
 * 
 * @return :: void
 */
void arbitrary_integer_print(ArbitraryInteger *arg) {

    for(VECTOR_TYPE_DATA i = 0; i < arg->magnitude.capacity; i++) {
        vector_print_size_t(vector_access_index(&(arg->magnitude), i));
    }
    return;
}


/**
 * @brief :: Initialise an arbitrary length integer
 *
 * @param :: *arg :: Item to be initialised
 * 
 * @return :: bool :: Indicates if initialisation was successfuly 
 */
bool arbitrary_integer_init(ArbitraryInteger *arg) {
    //arg->sign = '+';
    return vector_init(&(arg->magnitude), sizeof(size_t), 1);
}

/**
 * @brief :: Destroy an arbitrary length integer
 *
 * @param :: *arg :: Item to destroy
 * 
 * @return :: void
 */
void arbitrary_integer_destroy(ArbitraryInteger *arg) {
    vector_destroy(&(arg->magnitude));
    return;
}



/**
 * @brief :: Set an arbitrary length integer to some magnitude 
 *
 * @param :: *arg :: Destination magnitude
 * @param :: *data:: Array of size_t representing the magnitude
 * @param :: numel :: Size of magnitude array
 * 
 * @return :: void
 */
bool arbitrary_integer_set(ArbitraryInteger *arg, size_t *data, VECTOR_TYPE_DATA numel) {
    vector_destroy(&(arg->magnitude)); //This is really unoptimised - should implement something for this in vector.c
    return vector_append(&(arg->magnitude), data, numel);
}



/**
 * @brief :: Add two arbitrary length integers together. Magnitude is invalidated upon failure 
 *
 * @param :: *arg1 :: First argument and destination
 * @param :: *arg2 :: Second argument argument
 * 
 * @return :: bool 
 */
bool arbitrary_integer_add(ArbitraryInteger *arg1, ArbitraryInteger *arg2) {


    size_t padding = 0;
    //Make sure arg1 is big enough for result
    if(arg2->magnitude.top > arg1->magnitude.top) {
        if(vector_resize(&(arg1->magnitude), arg2->magnitude.top) == false) {
            return false;
        }
        //Zero out top bytes of arg1
        for(VECTOR_TYPE_DATA i = arg1->magnitude.top; i <= arg2->magnitude.top; i++) {
            vector_set_index(&(arg1->magnitude), &padding, i);
        }
    }


    size_t propagate = 0;
    for(VECTOR_TYPE_DATA i = 0; i < arg2->magnitude.top; i++) {

        size_t arg1Part = *(size_t*)vector_access_index(&(arg1->magnitude), i);
        size_t arg2Part = *(size_t*)vector_access_index(&(arg2->magnitude), i);

        size_t temp = arg1Part + arg2Part + propagate;

        if(temp > SIZE_T_MAX_PART) { //NOTE: SHOULD ALSO CHECK FOR OVERFLOW HERE

            propagate = temp - SIZE_T_MAX_PART; //Add to next part
            vector_set_index(&(arg1->magnitude), &padding, i);
        } else {
            vector_set_index(&(arg1->magnitude), &temp, i);
            propagate = 0;
        }
    }
    if(propagate != 0) { //Carry over
        if(vector_append(&(arg1->magnitude), &propagate, 1) == false) {
            return false;
        }
    }



    return true;
}

