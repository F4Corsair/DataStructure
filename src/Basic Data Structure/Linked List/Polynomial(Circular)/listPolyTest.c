#include <stdio.h>
#include <stdlib.h>
#include "circularListPolynomial.h"

int main(void)
{
    int readCoef, readExp;
    FILE *fp = fopen("poly1.txt", "r");
    Term *poly1 = polyInit();
    fscanf(fp, " %d %d", &readCoef, &readExp);
    while (!feof(fp))
    {
        polyAddTerm(poly1, readCoef, readExp);
        fscanf(fp, " %d %d", &readCoef, &readExp);
    }
    puts("[Poly1]");
    polyPrint(poly1);
    polyTerminate(poly1);

    fp = fopen("zeroPoly.txt", "r");
    Term *zeroPoly = polyInit();
    fscanf(fp, " %d %d", &readCoef, &readExp);
    while (!feof(fp))
    {
        polyAddTerm(zeroPoly, readCoef, readExp);
        fscanf(fp, " %d %d", &readCoef, &readExp);
    }
    puts("[zeroPoly]");
    polyPrint(zeroPoly);
    polyTerminate(zeroPoly);
}