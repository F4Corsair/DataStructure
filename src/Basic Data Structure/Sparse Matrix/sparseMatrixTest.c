#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

int main(void)
{
    puts("[Original Matrix]");
    Term *term = readNormalMatrix("matrix1.txt");
    printSparseMatrix(term);
    puts("");
    printOriginalMatrix(term);
    puts("[Transposed Matrix]");
    Term *trans = transpose(term);
    printOriginalMatrix(trans);
    freeSparseMatrix(term);
    freeSparseMatrix(trans);

    puts("\n[Original Matrix]");
    term = readSparseMatrix("sparseMatrix1.txt");
    printOriginalMatrix(term);
    puts("[Transposed Matrix]");
    trans = fastTranspose(term);
    printOriginalMatrix(trans);
    freeSparseMatrix(term);
    freeSparseMatrix(trans);
}