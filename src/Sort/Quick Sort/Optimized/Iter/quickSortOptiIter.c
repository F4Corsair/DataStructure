#include <stdio.h>
#include <stdlib.h>
#include "../../Iter/linkedStack.h"

/* Divide group about pivot, repeat this proecess until group size reach 1
 * 1. select a pivot record from among the records to be sorted
 * 2. divide records by 2 groups depends on comparison result about pivot record's key value
 * 3. iterate 1 - 2 process about each group independently until size of group been 1
 * time complexity : avergae O(nlogn) & unstable (worst : O(n^2))
 */

void swap(int *list, int a, int b)
{
    int temp = list[a];
    list[a] = list[b];
    list[b] = temp;
}

void sort3Asc(int *list, int left, int right)
{
    if (list[right - 1] > list[right])
        swap(list, right - 1, right);
    if (list[left] > list[right - 1])
        swap(list, left, right - 1);
    if (list[right - 1] > list[right])
        swap(list, right - 1, right);
}

void sort3Desc(int *list, int left, int right)
{
    if (list[right - 1] < list[right])
        swap(list, right - 1, right);
    if (list[left] < list[right - 1])
        swap(list, left, right - 1);
    if (list[right - 1] < list[right])
        swap(list, right - 1, right);
}

void _qSortAscIter(int *list, int left, int right)
{
    StackInfo *lstack = stackInit();
    StackInfo *rstack = stackInit();

    stackPush(lstack, left);
    stackPush(rstack, right);

    while (lstack->top != NULL)
    {
        Node *lnode = stackPop(lstack);
        left = lnode->data;
        free(lnode);
        Node *rnode = stackPop(rstack);
        right = rnode->data;
        free(rnode);
        sort3Asc(list, left, right);

        // if partition size is smaller or equal than 3, do sort3 and proceed to next one
        if (right - left < 3)
            continue;

        int lptr = left + 1;
        int rptr = right - 2;
        int pivot = list[right - 1];

        do
        {
            while (list[lptr] < pivot)
                lptr++;
            while (pivot < list[rptr])
                rptr--;

            if (lptr <= rptr)
            {
                swap(list, lptr, rptr);
                lptr++;
                rptr--;
            }
        } while (lptr <= rptr);

        if (left < rptr)
        {
            stackPush(lstack, left);
            stackPush(rstack, rptr);
        }
        if (lptr < right)
        {
            stackPush(lstack, lptr);
            stackPush(rstack, right);
        }
    }

    stackTerminate(lstack);
    stackTerminate(rstack);
}

void _qSortDescIter(int *list, int left, int right)
{
    StackInfo *lstack = stackInit();
    StackInfo *rstack = stackInit();

    stackPush(lstack, left);
    stackPush(rstack, right);

    while (lstack->top != NULL)
    {
        Node *lnode = stackPop(lstack);
        left = lnode->data;
        free(lnode);
        Node *rnode = stackPop(rstack);
        right = rnode->data;
        free(rnode);
        sort3Desc(list, left, right);
        int lptr = left + 1;
        int rptr = right - 2;
        int pivot = list[right - 1];

        do
        {
            while (list[lptr] > pivot)
                lptr++;
            while (pivot > list[rptr])
                rptr--;

            if (lptr <= rptr)
            {
                swap(list, lptr, rptr);
                lptr++;
                rptr--;
            }
        } while (lptr <= rptr);

        if (left < rptr)
        {
            stackPush(lstack, left);
            stackPush(rstack, rptr);
        }
        if (lptr < right)
        {
            stackPush(lstack, lptr);
            stackPush(rstack, right);
        }
    }

    stackTerminate(lstack);
    stackTerminate(rstack);
}

void quickSort(int *list, int size, int ascend)
{
    // call supbrocess
    int step, temp, j;
    if (ascend)
        _qSortAscIter(list, 0, size - 1);
    else
        _qSortDescIter(list, 0, size - 1);
}

void printList(int *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%3d ", list[i]);
    }
    puts("");
}

int main(void)
{
    int readSize, readNum;
    int *numList;
    FILE *fp = fopen("../../../Resources/numList.txt", "r");
    fscanf(fp, " %d", &readSize);
    while (!feof(fp))
    {
        numList = malloc(sizeof(int) * readSize);
        for (int i = 0; i < readSize; i++)
        {
            fscanf(fp, " %d", &readNum);
            numList[i] = readNum;
        }
        puts("\n[Original]");
        printList(numList, readSize);
        // sort
        puts("[Sorted_Ascend]");
        quickSort(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_Descend]");
        quickSort(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}