#include <stdio.h>
#include <stdlib.h>
#include "circularListPolynomial.h"
#define HEADER_EXPONENT -1
// notice : polynomial can't contain terms with its exponent is same as HEADER_EXPONENT

int intCmp(const int a, const int b)
{
    return a > b ? 1 : (a < b ? -1 : 0);
}

// this polynomial use circular linked list, which has header node
// header node doesn't have data, just indicates start of list
// why we use header node is express polynomial which has only a "0" term

Term *polyInit()
{
    Term *head = malloc(sizeof(Term));
    // coef and exp of header node is irrelevant
    // to make algorithm easier, we set exp of header node as HEADER_EXPONENT
    head->exponent = HEADER_EXPONENT;
    head->next = head;
    return head;
}

void polyAddTerm(Term *head, int coef, int exponent)
{
    if (coef == 0)
        return;
    Term *now = head->next;
    while (now->next->exponent != HEADER_EXPONENT)
    {
        now = now->next;
    }
    Term *newTerm = malloc(sizeof(Term));
    now->next = newTerm;
    newTerm->next = head;
    newTerm->coef = coef;
    newTerm->exponent = exponent;
}

Term *polyAdd(Term *headA, Term *headB)
{
    Term *newHead = polyInit();
    Term *ptrA = headA->next;
    Term *ptrB = headB->next;
    int flag = 0;
    do
    {
        switch (intCmp(ptrA->exponent, ptrB->exponent))
        {
        case 1:
            polyAddTerm(newHead, ptrA->coef, ptrA->exponent);
            ptrA = ptrA->next;
            break;
        case 0:
            if (ptrA->exponent == HEADER_EXPONENT)
            {
                flag = 1;
            }
            else
            {
                polyAddTerm(newHead, ptrA->coef + ptrB->coef, ptrA->exponent);
                ptrA = ptrA->next;
                ptrB = ptrB->next;
            }
            break;
        case -1:
            polyAddTerm(newHead, ptrB->coef, ptrB->exponent);
            ptrB = ptrB->next;
        }
    } while (!flag);
    return newHead;
}

void polyPrint(Term *head)
{
    Term *now = head->next;
    int exp;
    if (now->exponent == HEADER_EXPONENT)
    {
        printf("%5d\n", 0);
        return;
    }
    while ((exp = now->exponent) != HEADER_EXPONENT)
    {
        if (exp == 1)
            printf("%+3dx ", now->coef);
        else if (exp == 0)
            printf("%5d ", now->coef);
        else
            printf("%3dx^%-d ", now->coef, exp);
        now = now->next;
    }
    puts("");
}

void polyPrintInline(Term *head)
{
    polyPrint(head);
    polyTerminate(head);
}

void polyTerminate(Term *head)
{
    Term *now = head->next;
    Term *next;
    while (now->exponent != HEADER_EXPONENT)
    {
        next = now->next;
        free(now);
        now = next;
    }
    free(head);
}