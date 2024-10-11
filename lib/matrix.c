#include "matrix.h"
#define MACRO_ITERATE_MATRIX(matrixPtr, code)\
    for(size_t i = 0; i < matrixPtr->rows * matrixPtr->cols; i++) {\
        size_t currentIndex = i * matrixPtr->data.dataSize;;\
        void *current = (matrixPtr->data.data) + currentIndex;\
        code;\
    }






/**
 * @brief :: Print a matrix 
 *
 * @param :: *matrix :: Matrix to be printed 
 * @param :: print_element :: Function to print element 
 * 
 * @return :: void 
 */
void matrix_disp(Matrix *matrix, void print_element(void *element)) {

    MACRO_ITERATE_MATRIX(matrix, {
        print_element(current);
    });

    return;
}


/**
 * @brief :: Instantiates a matrix 
 *
 * @param :: *matrix :: Matrix to be initialised
 * @param :: dataSize :: Size of individual matrix element
 * @param :: rows :: Number of matrix rows 
 * @param :: cols :: Number of matrix columns 
 * 
 * @return :: bool :: Indication of whether matrix was successfully instantiated 
 */
bool matrix_init(Matrix *matrix, size_t dataSize, size_t rows, size_t cols) {

    matrix->rows = rows;
    matrix->cols = cols;
    if(vector_init(&(matrix->data), dataSize, rows * cols) == false) {
        return false;
    }

    return true;
}


/**
 * @brief :: Instantiates a matrix 
 *
 * @param :: *matrix :: Vector to be initialised
 * 
 * @return :: void
 */
void matrix_destroy(Matrix *matrix) {

    vector_destroy(&(matrix->data));
    matrix->cols = 0;
    matrix->rows = 0;

    return;
}


/**
 * @brief :: Fill a matrix with some values 
 *
 * @param :: *matrix :: Vector to be initialised
 * @param :: *data :: Items to be added to the matrix 
 * 
 * @return :: void 
 */
void matrix_fill(Matrix *matrix, void *data) {

    vector_fill(&(matrix->data), data);

    return;
}



/**
 * @brief :: Add two matricies to produce a third 
 *
 * @param :: *dest :: Resultant matrix 
 * @param :: *src1 :: Source matrix 1 
 * @param :: *src2 :: Source matrix 2
 * @param :: add_element :: Function to add element 
 * 
 * @return :: void 
 */
void matrix_add(Matrix *dest, Matrix *src1, Matrix *src2, void add_element(void *dest, void *src1, void *src2)) {


    MACRO_ITERATE_MATRIX(dest, {
        add_element(current, src1->data.data + currentIndex, src2->data.data + currentIndex);
    });


    return;
}




/**
 * @brief :: Sub two matricies to produce a third 
 *
 * @param :: *dest :: Resultant matrix 
 * @param :: *src1 :: Source matrix 1 
 * @param :: *src2 :: Source matrix 2
 * @param :: sub_element :: Function to subtract element 
 * 
 * @return :: void 
 */
void matrix_sub(Matrix *dest, Matrix *src1, Matrix *src2, void sub_element(void *dest, void *src1, void *src2)) {

    MACRO_ITERATE_MATRIX(dest, {
        sub_element(current, src1->data.data + currentIndex, src2->data.data + currentIndex);
    });

    return;
}






/**
 * @brief :: Multiply two matricies to produce a third 
 *
 * @param :: *dest :: Resultant matrix 
 * @param :: *src1 :: Source matrix 1 
 * @param :: *src2 :: Source matrix 2
 * @param :: multiply_element :: Function to multiply element 
 * 
 * @return :: void 
 */
void matrix_multiply(Matrix *dest, Matrix *src1, Matrix *src2, void multiply_element(void *dest, void *src1, void *src2)) {

    size_t size = src1->data.dataSize;
    for(size_t i = 0; i < src1->rows; i++) {
        for(size_t j = 0; j < src2->cols; j++) {
            //For each element - handles sum
            //void *src1Element = dest->data.data + i * size + j;
            //void *src2Element = dest->data.data + j * size + i;
            //void *= 0;

            multiply_element(destElement, src1Element, src2Element);
        }
    }

    return;
}



