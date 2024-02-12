#include <stdio.h>
#include <stdlib.h>
#include "../linkedList.h"

Node *stackPush(Node *top, const int num)
{
    return nodeAppendFront(top, num);
}

Node *stackPop(Node *top, int *num)
{
    return nodePopFront(top, num);
}

void stackTerminate(Node *top)
{
    nodeTerminate(top);
}

int main(void)
{
    Node *stackTop;
    stackTop = stackPush(stackTop, 10);
    stackTop = stackPush(stackTop, 20);
    stackTop = stackPush(stackTop, 30);

    int num;
    // notice : there's no pop warning when stack is empty
    stackTop = stackPop(stackTop, &num);
    printf("%d ", num);
    stackTop = stackPop(stackTop, &num);
    printf("%d ", num);
    stackTop = stackPop(stackTop, &num);
    printf("%d ", num);

    stackTerminate(stackTop);
}