#ifndef __PolynomialInt
#define __PolynomialInt
#define MAX_TERMS 100

typedef struct
{
    int coef;
    int exp;
} Polynomial;

int compareInt(int a, int b);

void polynomial_attach(Polynomial *terms, int *avail, int coef, int exp);

void polynomial_print(Polynomial *terms, int start, int finish);

void polynomial_add(Polynomial *terms, int *avail, int startA, int finishA, int startB, int finishB, int *startOut, int *finishOut);

void polynomial_sub(Polynomial *terms, int *avail, int startA, int finishA, int startB, int finishB, int *startOut, int *finishOut);

#endif