#ifndef STRINGS_H 
#define STRINGS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"


typedef struct String {

    size_t length; //NOTE: This includes the NULL terminator
    char *data;

} String;
typedef struct StringVector {

    String *data;

} StringVector;


void strings_print(String *string);
void strings_init(String *string);
void strings_destroy(String *string);
bool strings_set(String *string, char *data, size_t length);
char *strings_set_index(String *string, char character, size_t index);
size_t strings_length(String *string);
char *strings_read(String *string);
char *strings_read_index(String *string, size_t index);
bool strings_concatanate(String *dest, String *src);
bool strings_compare(String *arg1, String *arg2);



void strings_vector_init(StringVector *stringVector);


#endif 
      
      
      
      
      
      
      
      
