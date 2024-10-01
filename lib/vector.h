//23 September 2024
#ifndef VECTOR_H 
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


#define VECTOR_TYPE_DATA size_t 
#define VECTOR_TYPE_DATASIZE size_t 
#define VECTOR_TYPE_NUMEL size_t



typedef struct Vector {

    uint8_t *data;
    VECTOR_TYPE_DATA top;
    VECTOR_TYPE_DATA capacity;
    VECTOR_TYPE_DATASIZE dataSize;

} Vector;


void vector_print_size_t(void *ptr);
void vector_print_integer(void *ptr);
void vector_print_uint8_8(void *ptr);
void vector_disp(Vector *vector, void print_element(void *element));
bool vector_init(Vector *vector, VECTOR_TYPE_DATASIZE dataSize, VECTOR_TYPE_NUMEL numel);
void vector_destroy(Vector *vector);
bool vector_resize(Vector *vector, VECTOR_TYPE_NUMEL numel );
bool vector_append(Vector *vector, void *data, VECTOR_TYPE_NUMEL numel);
void *vector_access_index(Vector *vector, VECTOR_TYPE_DATA index);
void vector_set_index(Vector *vector, void *data, VECTOR_TYPE_DATA index);


#endif 



      
      
      
      