#include "strings.h"

#define MACRO_REALLOC(ptr, numel, size) realloc(ptr, numel * size)
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)
#define MACRO_FREE(ptr) free(ptr)

/**
 * @brief :: Print a string
 *
 * @param :: *string :: String to be printed
 * 
 * @return :: void
 */
void strings_print(String *string) {

    printf("%s",string->data);
    return;
}


/**
 * @brief :: Initialises a string with a specified datasize and initial capacity
 *
 * @param :: *string :: String to be initialised
 * 
 * @return :: void
 */
void strings_init(String *string) {

    string->data = NULL;
    string->length = 0;

    return;
}



/**
 * @brief :: Destroys a string and all associated memory 
 *
 * @param :: *string :: String to be destroyed 
 * 
 * @return :: void
 */
void strings_destroy(String *string) {

    free(string->data);
    string->length = 0;

    return;
}



/**
 * @brief :: Set a string to a character array. String is unchanged upon failure
 *
 * @param :: *string :: String to be initialised
 * @param :: *data :: String to bet used 
 * @param :: length :: Length of the string to be used (does not include NULL terminator)
 * 
 * @return :: bool :: Indication of string was successfully set 
 */
bool strings_set(String *string, void *data, size_t length) {

    length++; //Account for NULL terminator
    string->data = MACRO_REALLOC(string->data, length, sizeof(char));
    if(string->data == NULL) {
        return false;
    }

    string->length = length;
    MACRO_MEMCPY(string->data, data, length);

    return true;
}




/**
 * @brief :: Length of a string structure 
 *
 * @param :: *string :: String of interest 
 * 
 * @return :: size_t :: Length of the string 
 */
size_t strings_length(String *string) {
    return string->length;
}



/**
 * @brief :: Read a string from a structure
 *
 * @param :: *string :: String to be read 
 * 
 * @return :: char* :: String as a char array 
 */
char *strings_read(String *string) {
    return string->data;
}




/**
 * @brief :: Concatanate two strings together. The destination is unmodified upon failure
 *
 * @param :: *dest :: Destination string 
 * @param :: *src :: Source string 
 * 
 * @return :: bool :: Indication of concatanation was successfull 
 */
bool strings_concatanate(String *dest, String *src) {

    dest->data = MACRO_REALLOC(dest->data, dest->length + src->length, sizeof(char));
    if(dest->data == NULL) {
        return false;
    }
    MACRO_MEMCPY(dest->data + dest->length - 1, src->data, src->length);
    dest->length += src->length;

    return true;
}


/**
 * @brief :: Compare two strings to see if they are the same 
 *
 * @param :: *arg1:: First string 
 * @param :: *arg2:: Second string 
 * 
 * @return :: bool :: Indication of if the strings are the same 
 */
bool strings_compare(String *arg1, String *arg2) {

    if(strcmp(arg1->data, arg2->data) == 0) {
        return true;
    } else {
        return false;
    }

    return true;
}







