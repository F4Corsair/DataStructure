#ifndef __circularListPoly
#define __circularListPoly

typedef struct _term
{
    int coef;
    int exponent;
    struct _term *next;
} Term;

int intCmp(const int a, const int b);

Term *polyInit();

void polyAddTerm(Term *head, int coef, int exponent);

Term *polyAdd(Term *headA, Term *headB);

void polyPrint(Term *head);

void polyPrintInline(Term *head);

void polyTerminate(Term *head);

#endif