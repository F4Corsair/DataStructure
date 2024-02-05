#ifndef __IntStack
#define __IntStack

typedef struct
{
    int maxSize;
    int top;
    int *stack;
} IntStack;

int stackInitialize(IntStack *s, int maxSize);

int stackPush(IntStack *s, int value);

int stackPop(IntStack *s, int *value);

int stackPeek(const IntStack *s, int *value);

void stackClear(IntStack *s);

int stackCapacity(const IntStack *s);

int stackSize(const IntStack *s);

int isStackEmpty(const IntStack *s);

int isStackFull(const IntStack *s);

int stackSearch(const IntStack *s, int searchNum);

void stackPrint(const IntStack *s);

void stackTerminate(IntStack *s);

#endif