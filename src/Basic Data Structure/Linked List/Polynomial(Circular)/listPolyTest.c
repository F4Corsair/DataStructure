#include <stdio.h>
#include <stdlib.h>
#include "circularListPolynomial.h"

int main(void)
{
    int readCoef, readExp;
    // poly1 read & print
    FILE *fp = fopen("poly1.txt", "r");
    Term *poly1 = polyInit();
    fscanf(fp, " %d %d", &readCoef, &readExp);
    while (!feof(fp))
    {
        polyAddTerm(poly1, readCoef, readExp);
        fscanf(fp, " %d %d", &readCoef, &readExp);
    }
    fclose(fp);
    puts("[poly1]");
    polyPrint(poly1);

    // zeor poly read & print
    fp = fopen("zeroPoly.txt", "r");
    Term *zeroPoly = polyInit();
    fscanf(fp, " %d %d", &readCoef, &readExp);
    while (!feof(fp))
    {
        polyAddTerm(zeroPoly, readCoef, readExp);
        fscanf(fp, " %d %d", &readCoef, &readExp);
    }
    fclose(fp);
    puts("[zeroPoly]");
    polyPrint(zeroPoly);

    // poly2 read & print
    fp = fopen("poly2.txt", "r");
    Term *poly2 = polyInit();
    fscanf(fp, " %d %d", &readCoef, &readExp);
    while (!feof(fp))
    {
        polyAddTerm(poly2, readCoef, readExp);
        fscanf(fp, " %d %d", &readCoef, &readExp);
    }
    fclose(fp);
    puts("[poly2]");
    polyPrint(poly2);

    // poly add
    puts("[poly1 + poly2]");
    polyPrintInline(polyAdd(poly1, poly2));
    puts("[poly1 + zeroPoly]");
    polyPrintInline(polyAdd(poly1, zeroPoly));

    polyTerminate(poly1);
    polyTerminate(poly2);
    polyTerminate(zeroPoly);
}