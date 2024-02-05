#ifndef __SparseMatrix
#define __SparseMatrix

typedef struct
{
    int row;
    int col;
    int val;
} Term;
// in sparse matrix, index 0 entry describes data of matrix (row size, col size, # of nonzero entry)

Term *readNormalMatrix(char *fileName);

Term *readSparseMatrix(char *fileName);

void freeSparseMatrix(Term *term);

void printSparseMatrix(Term *term);

void printOriginalMatrix(Term *term);

// Notice : The matrices should be offered in ascending order if you want to Transpose it
Term *transpose(Term *a);

Term *fastTranspose(Term *a);

void copyMatrix(const Term *src, Term *dest);

Term *multiplicateMatrix(const Term *_a, const Term *_b);

#endif