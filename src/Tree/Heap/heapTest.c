#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int main(void)
{
    puts("=Max Heap=");
    Heap *maxHeap = heapInitialize();
    FILE *fp = fopen("in.txt", "r");
    char readName[MAX_NAME_SIZE];
    int readScore, readOrder;
    fscanf(fp, "%s %d %d", readName, &readOrder, &readScore);
    while (!feof(fp))
    {
        maxHeapInsert(maxHeap, readScore, readName);
        levelOrderPrint(maxHeap);
        fscanf(fp, "%s %d %d", readName, &readOrder, &readScore);
    }
    fclose(fp);

    Data *popData = maxHeapDelete(maxHeap);
    while (popData != NULL)
    {
        printf("Pop : [%s] (%d)\n", popData->name, popData->score);
        free(popData);
        levelOrderPrint(maxHeap);
        popData = maxHeapDelete(maxHeap);
    }

    heapTerminate(maxHeap);

    puts("\n=Min Heap=");
    Heap *minHeap = heapInitialize();
    fp = fopen("in.txt", "r");
    fscanf(fp, "%s %d %d", readName, &readOrder, &readScore);
    while (!feof(fp))
    {
        minHeapInsert(minHeap, readScore, readName);
        levelOrderPrint(minHeap);
        fscanf(fp, "%s %d %d", readName, &readOrder, &readScore);
    }
    fclose(fp);

    popData = minHeapDelete(minHeap);
    while (popData != NULL)
    {
        printf("Pop : [%s] (%d)\n", popData->name, popData->score);
        free(popData);
        levelOrderPrint(minHeap);
        popData = minHeapDelete(minHeap);
    }

    heapTerminate(minHeap);
}