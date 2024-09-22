//23 September 2024
#ifndef VECTOR_H 
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>


#define TYPE_TOP short unsigned int
#define TYPE_CAPACITY short unsigned int
#define TYPE_DATASIZE short unsigned int
#define TYPE_NUMEL size_t
#define TYPE_INDEX short unsigned int


#define MACRO_MALLOC(numel, size) malloc(numel * size)
#define MACRO_REALLOC(ptr, numel, size) realloc(ptr, numel * size)
#define CONST_REALLOC_EXPANSION 2
#define MACRO_MEMCPY(dest, src, n) memcpy(dest, src, n)

#define MACRO_DISP(capacity, top, dataSize) \
    printf("\tCapacity: %hu\n\tTop: %hu\n\tData size: %hu\n\n",capacity, top, dataSize);


typedef struct Vector {

    uint8_t *data;
    TYPE_TOP top;
    TYPE_CAPACITY capacity;
    TYPE_DATASIZE dataSize;

} Vector;


void vector_disp(Vector *vector, void print_element(void *element));
bool vector_init(Vector *vector, TYPE_DATASIZE dataSize, TYPE_NUMEL numel);
bool vector_destroy(Vector *vector);
bool vector_resize(Vector *vector, TYPE_NUMEL numel );
bool vector_append(Vector *vector, void *data, TYPE_NUMEL numel);
void *vector_access_index(Vector *vector, TYPE_INDEX index);
void vector_set_index(Vector *vector, void *data, TYPE_INDEX index);


#endif 



      
      
      
      