#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

int main(void)
{
    puts("[Original Matrix]");
    Term *term1 = readNormalMatrix("matrix1.txt");
    printSparseMatrix(term1);
    puts("");
    printOriginalMatrix(term1);
    puts("[Transposed Matrix]");
    Term *trans1 = transpose(term1);
    printOriginalMatrix(trans1);
    freeSparseMatrix(term1);
    freeSparseMatrix(trans1);

    puts("\n[Original Matrix]");
    Term *term2 = readSparseMatrix("sparseMatrix1.txt");
    printOriginalMatrix(term2);
    puts("[Transposed Matrix]");
    Term *trans2 = fastTranspose(term2);
    printOriginalMatrix(trans2);

    puts("[Matrix Multiplication]");
    term1 = readSparseMatrix("sparseMatrix2.txt");
    Term *term3 = multiplicateMatrix(term1, term2);
    printOriginalMatrix(term3);

    freeSparseMatrix(term1);
    freeSparseMatrix(term2);
    freeSparseMatrix(trans2);
    freeSparseMatrix(term3);
}