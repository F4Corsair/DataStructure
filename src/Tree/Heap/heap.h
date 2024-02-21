#ifndef __Heap
#define __Heap
#define MAX_NAME_SIZE 20
#define HEAP_INI_SIZE 8

typedef struct
{
    int score; // key value
    char name[MAX_NAME_SIZE];
} Data;

typedef struct
{
    int capacity;
    int size;   // # of data, also indicates index of last element
    Data *data; // data index starts from 1
} Heap;

int isHeapFull(Heap *heap);

int isHeapEmpty(Heap *heap);

Heap *heapInitialize();

void heapTerminate(Heap *heap);

void maxHeapInsert(Heap *heap, int score, char *name);

Data *maxHeapDelete(Heap *heap);

void minHeapInsert(Heap *heap, int score, char *name);

Data *minHeapDelete(Heap *heap);

void levelOrderPrint(Heap *heap);

#endif