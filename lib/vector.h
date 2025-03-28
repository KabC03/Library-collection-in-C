//23 September 2024
#ifndef VECTOR_H 
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>



typedef struct Vector {

    uint8_t *data; //Dont use a FLM here since it means entire structure needs to be reallocated upon reisze
    size_t top;
    size_t capacity;
    uint8_t dataSize;

} Vector;


void vector_print_size_t(void *ptr);
void vector_print_integer(void *ptr);
void vector_print_uint8_t(void *ptr);
size_t vector_get_size(Vector *vector);
void vector_disp(Vector *vector, void print_element(void *element));
bool vector_expand(Vector *vector, size_t numel);
bool vector_init(Vector *vector, uint8_t dataSize, size_t numel);
void vector_destroy(Vector *vector);
bool vector_resize(Vector *vector, size_t numel );
void *vector_append(Vector *vector, void *data, size_t numel);
void *vector_access_index(Vector *vector, size_t index);
void *vector_set_index(Vector *vector, void *data, size_t index);
void vector_fill(Vector *vector, void *data);
void *vector_fread_append(Vector *vector, FILE *fptr, size_t numel);
void vector_xor_swap(Vector *vector, size_t index1, size_t index2);
void *vector_pop(Vector *vector);


#endif 



      
      
      
      
