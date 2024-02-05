#include <stdio.h>
#include <stdlib.h>
#include "polynomial_int.h"

/*
 * to express polynomial which is sparse, we use array representation
 * with start-end position indicators for each term
 * that is, we divide 'coef-exponent' array by using 'start-finish' pair
 */

int main(void)
{
    int startA, startB, finishA, finishB, startD, finishD;
    Polynomial terms[MAX_TERMS];
    int avail = 0;

    // read data from text file
    int readCoef, readExp;
    FILE *fp = fopen("poly1.txt", "r");
    startA = avail;
    while (!feof(fp))
    {
        fscanf(fp, " %d %d", &readCoef, &readExp);
        polynomial_attach(terms, &avail, readCoef, readExp);
    }
    finishA = avail - 1;
    fclose(fp);
    fp = fopen("poly2.txt", "r");
    startB = avail;
    while (!feof(fp))
    {
        fscanf(fp, " %d %d", &readCoef, &readExp);
        polynomial_attach(terms, &avail, readCoef, readExp);
    }
    finishB = avail - 1;
    fclose(fp);

    // print result
    puts("Polynomial A");
    polynomial_print(terms, startA, finishA);
    puts("\nPolynomial B");
    polynomial_print(terms, startB, finishB);

    // polynomial addition
    polynomial_add(terms, &avail, startA, finishA, startB, finishB, &startD, &finishD);
    puts("\nA + B");
    polynomial_print(terms, startD, finishD);

    // polynomial subtraction
    polynomial_sub(terms, &avail, startA, finishA, startB, finishB, &startD, &finishD);
    puts("\nA - B");
    polynomial_print(terms, startD, finishD);

    polynomial_sub(terms, &avail, startA, finishA, startA, finishA, &startD, &finishD);
    puts("\nA - A");
    polynomial_print(terms, startD, finishD);
    puts("");
}