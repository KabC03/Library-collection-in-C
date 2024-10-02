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


void strings_print(String *string);
void strings_init(String *string);
void strings_destroy(String *string);
bool strings_set(String *string, void *data, size_t length);
size_t strings_length(String *string);
char *strings_read(String *string);
bool strings_concatanate(String *dest, String *src);



#endif 
      
      
      
      
      
      
      
      
