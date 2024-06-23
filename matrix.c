#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

matrix createMatrix(int nr, int nc){
    matrix m;
    m.rows=nr;
    m.columns=nc;
    m.cells = (int**) malloc(nr * sizeof(int*));

    int i;

    for (i = 0; i < nr; i++){
        m.cells[i] = (int*) calloc(nc, sizeof(int));
    }

    return m;
}

void matrixZeros(matrix m) {
    int i, j;
    for (i = 0; i < m.rows; i++) {
        for (j = 0; j < m.columns; j++) {
            m.cells[i][j] = 0;
        }
    }
}

void printMatrix(matrix m){
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.columns; j++) {
            printf("%4d", m.cells[i][j]);
        }
        printf("\n");
    }
}