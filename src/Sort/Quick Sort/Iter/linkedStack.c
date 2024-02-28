#include <stdio.h>
#include <stdlib.h>
#include "linkedStack.h"

StackInfo *stackInit()
{
    StackInfo *stack = malloc(sizeof(StackInfo));
    stack->top = NULL;
    return stack;
}

void stackPush(StackInfo *stack, int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->next = stack->top;
    stack->top = newNode;
    newNode->data = data;
}

Node *stackPop(StackInfo *stack)
{
    if (stack->top == NULL)
    {
        return NULL;
    }
    Node *ret = stack->top;
    stack->top = stack->top->next;
    return ret;
}

void stackTerminate(StackInfo *stack)
{
    Node *ptr = stack->top;
    while (ptr != NULL)
    {
        free(ptr);
        ptr = ptr->next;
    }
    free(stack);
}