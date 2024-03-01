#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

/* Heaps are frequently used to implement priority queues
 * Priority Queue : queue that element to be deleted is one with highest(or lowest) priority (=placed on root node)
 * Max(Min) Heap : complete binary tree that is also a max(min) tree
 * max heap -> maximum value pop first / min heap -> minimum value pop first
 * Heap Insertion : since heap is complete binary, new item will placed in last index of tree at first
 * and that item traverses to appropriate place by bubbling up(compare-swap procedure)
 * Heap Deletion : if item taken from root of the heap, then, tree needs to be restructed (heap after deletion violate form of complete binary tree)
 * to reconstruct it, first, we take last index element to root. and re-position it by bubbling swap until it reaches appropriate place
 * Notice : if heap element index starts from 1, you can easily access to parent / child index by just multiply(or *2+1) or divide by 2
 * if you want to set first index to 0, you need to use another parent / child index access method
 * if current index is "i", then its parent index is "(i-1)/2". its childs index is "i*2+1" and "i*2+2"
 * Time complexity of Insertion & Deletion of heap are O(logn)
 */

int isHeapFull(Heap *heap)
{
    return heap->capacity <= heap->size + 1;
}

int isHeapEmpty(Heap *heap)
{
    return heap->size < 1;
}

Heap *heapInitialize()
{
    Heap *new = malloc(sizeof(Heap));
    new->data = malloc(sizeof(Data) * HEAP_INI_SIZE);
    new->size = 0;
    new->capacity = HEAP_INI_SIZE;
    return new;
}

void heapTerminate(Heap *heap)
{
    free(heap->data);
    free(heap);
}

void maxHeapInsert(Heap *heap, int score, char *name)
{
    if (isHeapFull(heap))
    {
        // double its capacity
        heap->data = realloc(heap->data, sizeof(Data) * heap->capacity * 2);
        heap->capacity = heap->capacity * 2;
    }
    int idx = ++(heap->size);
    // at first, new item insert as last index of tree
    // notice : first index of heap->data list is 1
    while ((idx != 1) && (score > heap->data[idx / 2].score))
    {
        // until new item's score(key) has higher value, pull down data from parent node repeatedly
        heap->data[idx].score = heap->data[idx / 2].score;
        strcpy(heap->data[idx].name, heap->data[idx / 2].name);
        idx = idx / 2;
    }
    // at last, set data of new node. idx will indicate its appropriate index
    heap->data[idx].score = score;
    strcpy(heap->data[idx].name, name);
}

Data *maxHeapDelete(Heap *heap)
{
    if (isHeapEmpty(heap))
    {
        // fprintf(stderr, "Heap is Empty\n");
        return NULL;
    }
    Data *minValue = malloc(sizeof(Data));
    strcpy(minValue->name, heap->data[1].name);
    minValue->score = heap->data[1].score;

    // move last element of tree as first element of tree
    strcpy(heap->data[1].name, heap->data[heap->size].name);
    heap->data[1].score = heap->data[heap->size].score;
    heap->size--;

    int parentIdx = 1, childIdx = 2;
    while (childIdx <= heap->size)
    {
        // set childIdx as element which has bigger score(key)
        if (childIdx < heap->size && heap->data[childIdx].score < heap->data[childIdx + 1].score)
            childIdx++;
        // if parentIdx found appropriate place (= place last element on childIdx brokes max Heap structure), break
        if (heap->data[heap->size + 1].score > heap->data[childIdx].score)
            break;
        // else, step down to descendant (push child data to parent index)
        strcpy(heap->data[parentIdx].name, heap->data[childIdx].name);
        heap->data[parentIdx].score = heap->data[childIdx].score;
        parentIdx = childIdx;
        childIdx *= 2;
    }
    strcpy(heap->data[parentIdx].name, heap->data[heap->size + 1].name);
    heap->data[parentIdx].score = heap->data[heap->size + 1].score;

    return minValue;
}

void minHeapInsert(Heap *heap, int score, char *name)
{
    if (isHeapFull(heap))
    {
        // double its capacity
        heap->data = realloc(heap->data, sizeof(Data) * heap->capacity * 2);
        heap->capacity = heap->capacity * 2;
    }
    int idx = ++(heap->size);
    // at first, new item insert as last index of tree
    // notice : first index of heap->data list is 1
    while ((idx != 1) && (score < heap->data[idx / 2].score))
    {
        // until new item's score(key) has lower value, pull down data from parent node repeatedly
        heap->data[idx].score = heap->data[idx / 2].score;
        strcpy(heap->data[idx].name, heap->data[idx / 2].name);
        idx = idx / 2;
    }
    // at last, set data of new node. idx will indicate its appropriate index
    heap->data[idx].score = score;
    strcpy(heap->data[idx].name, name);
}

Data *minHeapDelete(Heap *heap)
{
    if (isHeapEmpty(heap))
    {
        // fprintf(stderr, "Heap is Empty\n");
        return NULL;
    }
    Data *minValue = malloc(sizeof(Data));
    strcpy(minValue->name, heap->data[1].name);
    minValue->score = heap->data[1].score;

    // move last element of tree as first element of tree
    strcpy(heap->data[1].name, heap->data[heap->size].name);
    heap->data[1].score = heap->data[heap->size].score;
    heap->size--;

    int parentIdx = 1, childIdx = 2;
    while (childIdx <= heap->size)
    {
        // set childIdx as element which has bigger score(key)
        if (childIdx < heap->size && heap->data[childIdx].score > heap->data[childIdx + 1].score)
            childIdx++;
        // if parentIdx found appropriate place (= place last element on childIdx brokes max Heap structure), break
        if (heap->data[heap->size + 1].score < heap->data[childIdx].score)
            break;
        // else, step down to descendant (push child data to parent index)
        strcpy(heap->data[parentIdx].name, heap->data[childIdx].name);
        heap->data[parentIdx].score = heap->data[childIdx].score;
        parentIdx = childIdx;
        childIdx *= 2;
    }
    strcpy(heap->data[parentIdx].name, heap->data[heap->size + 1].name);
    heap->data[parentIdx].score = heap->data[heap->size + 1].score;

    return minValue;
}

void levelOrderPrint(Heap *heap)
{
    if (heap == NULL || heap->size < 1)
        return;
    for (int i = 1; i <= heap->size; i++)
    {
        printf("[%s] ", heap->data[i].name);
    }
    puts("");
}