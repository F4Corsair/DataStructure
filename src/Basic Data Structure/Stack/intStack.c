#include <stdio.h>
#include <stdlib.h>
#include "intStack.h"

int stackInitialize(IntStack *s, int maxSize)
{
    s->top = 0;
    if ((s->stack = malloc(sizeof(int) * maxSize)) == NULL)
    {
        s->maxSize = 0;
        return -1;
    }
    s->maxSize = maxSize;
    return 0;
}

int stackPush(IntStack *s, int value)
{
    if (s->top >= s->maxSize)
        return -1;
    s->stack[s->top++] = value;
    return 0;
}

int stackPop(IntStack *s, int *value)
{
    if (s->top <= 0)
        return -1;
    *value = s->stack[s->top - 1];
    return 0;
}

int stackPeek(const IntStack *s, int *value)
{
    if (s->top <= 0)
        return -1;
    *value = s->stack[s->top - 1];
    return 0;
}

void stackClear(IntStack *s)
{
    s->top = 0;
}

int stackCapacity(const IntStack *s)
{
    return s->maxSize;
}

int stackSize(const IntStack *s)
{
    return s->top;
}

int isStackEmpty(const IntStack *s)
{
    return s->top <= 0;
}

int isStackFull(const IntStack *s)
{
    return s->top >= s->maxSize;
}

int stackSearch(const IntStack *s, int searchNum)
{
    for (int i = s->top - 1; i >= 0; i--)
        if (s->stack[i] == searchNum)
            return i;
    return -1;
}

void stackPrint(const IntStack *s)
{
    for (int i = 0; i < s->top; i++)
        printf("%d ", s->stack[i]);
    puts("");
}

void stackTerminate(IntStack *s)
{
    if (s->stack != NULL)
        free(s->stack);
    s->maxSize = s->top = 0;
}