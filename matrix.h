#ifndef DEF_MATRIX
#define DEF_MATRIX

typedef struct {
    int rows;
    int columns;
    int** cells;
} matrix;


/* @requires nr (number of rows) >= 0 and nc (number of colums) >= 0 
   @assigns nothing
   @ensures create a nr x nc matrix */
matrix createMatrix(int nr, int nc);

/* @requires m a valid matrix
   @assigns nothing
   @ensures initialize the matrix with zeros */
void matrixZeros(matrix m);

/* @requires nothing
   @assigns nothing
   @ensures : print the matrix */
void printMatrix(matrix m);

#endif