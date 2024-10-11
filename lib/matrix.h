//10 October 2024
#ifndef MATRIX_H 
#define MATRIX_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vector.h"

typedef struct Matrix {

    size_t rows;
    size_t cols;

    Vector data;

} Matrix;



void matrix_disp(Matrix *matrix, void print_element(void *element));
bool matrix_init(Matrix *matrix, size_t dataSize, size_t rows, size_t cols);
void matrix_destroy(Matrix *matrix);
void matrix_fill(Matrix *matrix, void *data);
void matrix_add(Matrix *dest, Matrix *src1, Matrix *src2, void add_element(void *dest, void *src1, void *src2));
void matrix_sub(Matrix *dest, Matrix *src1, Matrix *src2, void sub_element(void *dest, void *src1, void *src2));
void matrix_multiply(Matrix *dest, Matrix *src1, Matrix *src2, void multiply_element(void *dest, void *src1, void *src2));

#endif 



      
      
      
      