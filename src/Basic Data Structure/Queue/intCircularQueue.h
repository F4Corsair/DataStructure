#ifndef __IntCircularQ
#define __IntCircularQ

typedef struct
{
    int maxSize;
    int size;
    int front;
    int rear;
    int *que;
} IntQueue;

int qInitialize(IntQueue *q, int maxSize);

int enqueue(IntQueue *q, int value);

int dequeue(IntQueue *q, int *value);

int qPeek(const IntQueue *q, int *value);

void qClear(IntQueue *q);

int qCapacity(const IntQueue *q);

int qSize(const IntQueue *q);

int isQEmpty(const IntQueue *q);

int isQFull(const IntQueue *q);

int qSearch(const IntQueue *q, int searchNum);

void qPrint(const IntQueue *q);

void qTerminate(IntQueue *q);

#endif