#ifndef __linkedStack
#define __linkedStack

typedef struct _Node
{
    int data;
    struct _Node *next;
} Node;

typedef struct
{
    Node *top;
} StackInfo;

StackInfo *stackInit();

void stackPush(StackInfo *stack, int data);

Node *stackPop(StackInfo *stack);

void stackTerminate(StackInfo *stack);

#endif