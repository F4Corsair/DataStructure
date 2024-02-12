#include <stdio.h>
#include <stdlib.h>
#include "../linkedList.h"

void queueInit(LinkedList *q)
{
    linkedListInit(q);
}

void enqueue(LinkedList *q, const int num)
{
    listAppendRear(q, num);
}

int dequeue(LinkedList *q)
{
    return listPopFront(q);
}

void queueTerminate(LinkedList *q)
{
    listTerminate(q);
}

int main(void)
{
    LinkedList queue;
    queueInit(&queue);
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));
    printf("%d ", dequeue(&queue));
    queueTerminate(&queue);
}