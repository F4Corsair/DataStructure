#include <stdio.h>
#include <stdlib.h>
#include "polynomial_int.h"

int compare_int(int a, int b)
{
    return a > b ? 1 : (a < b ? -1 : 0);
}

// in polynomial_attach, you have to manage start-finish data yourself
// if you handle sparse polynomial data, it doesn't support revise operation
// its object is making new polynomial by attaching each terms one by one
void polynomial_attach(Polynomial *terms, int *avail, int coef, int exp)
{
    if (*avail >= MAX_TERMS)
    {
        printf("Too many terms in a polynomial object");
        exit(1);
    }
    terms[*avail].coef = coef;
    terms[(*avail)++].exp = exp;
}

void polynomial_print(Polynomial *terms, int start, int finish)
{
    if (finish == 0)
        return;
    int exp;
    exp = terms[start].exp;
    if (exp == 1)
        printf("%3dx ", terms[start].coef);
    else if (exp == 0)
        printf("%3d ", terms[start].coef);
    else
        printf("%3dx^%-d ", terms[start].coef, exp);
    for (int i = start + 1; i <= finish; i++)
    {
        exp = terms[i].exp;
        if (exp == 1)
            printf("%+3dx ", terms[i].coef);
        else if (exp == 0)
            printf("%+3d ", terms[i].coef);
        else
            printf("%+3dx^%-d ", terms[i].coef, exp);
    }
}

void polynomial_add(Polynomial *terms, int *avail, int startA, int finishA, int startB, int finishB, int *startOut, int *finishOut)
{
    *startOut = *avail;
    while (startA <= finishA && startB <= finishB)
    {
        switch (compare_int(terms[startA].exp, terms[startB].exp))
        {
        case -1:
            polynomial_attach(terms, avail, terms[startB].coef, terms[startB].exp);
            startB++;
            break;
        case 0:
            polynomial_attach(terms, avail, terms[startA].coef + terms[startB].coef, terms[startA].exp);
            startA++;
            startB++;
            break;
        case 1:
            polynomial_attach(terms, avail, terms[startA].coef, terms[startA].exp);
            startA++;
        }
    }
    for (; startA <= finishA; startA++)
        polynomial_attach(terms, avail, terms[startA].coef, terms[startA].exp);
    for (; startB <= finishB; startB++)
        polynomial_attach(terms, avail, terms[startB].coef, terms[startB].exp);

    *finishOut = *avail - 1;
}

void polynomial_sub(Polynomial *terms, int *avail, int startA, int finishA, int startB, int finishB, int *startOut, int *finishOut)
{
    int coef;
    *startOut = *avail;
    while (startA <= finishA && startB <= finishB)
    {
        switch (compare_int(terms[startA].exp, terms[startB].exp))
        {
        case -1:
            polynomial_attach(terms, avail, terms[startB].coef, terms[startB].exp);
            startB++;
            break;
        case 0:
            coef = terms[startA].coef - terms[startB].coef;
            if (coef)
                polynomial_attach(terms, avail, coef, terms[startA].exp);
            startA++;
            startB++;
            break;
        case 1:
            polynomial_attach(terms, avail, terms[startA].coef, terms[startA].exp);
            startA++;
        }
    }
    for (; startA <= finishA; startA++)
        polynomial_attach(terms, avail, terms[startA].coef, terms[startA].exp);
    for (; startB <= finishB; startB++)
        polynomial_attach(terms, avail, terms[startB].coef, terms[startB].exp);

    if (*startOut == *avail)
        polynomial_attach(terms, avail, 0, 0);
    *finishOut = *avail - 1;
}