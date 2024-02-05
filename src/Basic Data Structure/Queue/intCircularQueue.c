#include <stdio.h>
#include <stdlib.h>
#include "intCircularQueue.h"

int qInitialize(IntQueue *q, int maxSize)
{
    q->size = q->front = q->rear = 0;
    if ((q->que = malloc(sizeof(int) * maxSize)) == NULL)
    {
        q->maxSize = 0;
        return -1;
    }
    q->maxSize = maxSize;
    return 0;
}

int enqueue(IntQueue *q, int value)
{
    if (q->size >= q->maxSize)
        return -1;
    else
    {
        q->size++;
        q->que[q->rear++] = value;
        if (q->rear == q->maxSize)
            q->rear = 0;
        return 0;
    }
}

int dequeue(IntQueue *q, int *value)
{
    if (q->size <= 0)
        return -1;
    else
    {
        q->size--;
        *value = q->que[q->front++];
        if (q->front == q->maxSize)
            q->front = 0;
        return 0;
    }
}

int qPeek(const IntQueue *q, int *value)
{
    if (q->size <= 0)
        return -1;
    *value = q->que[q->front];
    return 0;
}

void qClear(IntQueue *q)
{
    q->size = q->front = q->rear = 0;
}

int qCapacity(const IntQueue *q)
{
    return q->maxSize;
}

int qSize(const IntQueue *q)
{
    return q->size;
}

int isQEmpty(const IntQueue *q)
{
    return q->size <= 0;
}

int isQFull(const IntQueue *q)
{
    return q->size >= q->maxSize;
}

int qSearch(const IntQueue *q, int searchNum)
{
    int idx;
    for (int i = 0; i <= q->size; i++)
        if (q->que[idx = (i + q->front) % q->maxSize] == searchNum)
            return idx;
    return -1;
}

void qPrint(const IntQueue *q)
{
    if (q->size <= 0)
        printf("Queue is Empty!");
    for (int i = 0; i < q->size; i++)
        printf("%d ", q->que[(i + q->front) % q->maxSize]);
    puts("");
}

void qTerminate(IntQueue *q)
{
    if (q->que != NULL)
        free(q->que);
    q->maxSize = q->front = q->rear = q->size = 0;
}