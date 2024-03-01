#include <stdio.h>
#include <stdlib.h>

/* at first, divde full list to multiple sublists wich has only one elements
 * then, merge 2 sublist to one list, iterate this proecess to reduce the number of sublist by half
 * this will continue until only one sublist left
 * time complexity : O(nlogn) & stable
 */

void _mergeAsc(int *src, int *dest, int left, int middle, int right)
{
    int ptrLeft = left;
    int ptrRight = middle + 1;
    int destPtr = left;
    while (ptrLeft <= middle && ptrRight <= right)
    {
        if (src[ptrLeft] <= src[ptrRight])
            dest[destPtr++] = src[ptrLeft++];
        else
            dest[destPtr++] = src[ptrRight++];
    }
    if (middle < ptrLeft) // left part of src == left part of dest -> copy right part of src to dest
        while (ptrRight <= right)
            dest[destPtr++] = src[ptrRight++];
    else // right part of src is all copied to dest -> copy left one of left part in src to dest
        while (ptrLeft <= middle)
            dest[destPtr++] = src[ptrLeft++];
}

void _mergePassAsc(int *src, int *dest, int size, int step)
{
    int lastIdx = size - 1;
    int left;
    for (left = 0; left <= lastIdx - 2 * step + 1; left += 2 * step)
        _mergeAsc(src, dest, left, left + step - 1, left + 2 * step - 1);
    if (left + step - 1 < lastIdx)
        _mergeAsc(src, dest, left, left + step - 1, lastIdx);
    else
        for (int j = left; j <= lastIdx; j++)
            dest[j] = src[j];
}

void _mergeDesc(int *src, int *dest, int left, int middle, int right)
{
    int ptrLeft = left;
    int ptrRight = middle + 1;
    int destPtr = left;
    while (ptrLeft <= middle && ptrRight <= right)
    {
        if (src[ptrLeft] >= src[ptrRight])
            dest[destPtr++] = src[ptrLeft++];
        else
            dest[destPtr++] = src[ptrRight++];
    }
    if (middle < ptrLeft) // left part of src == left part of dest -> copy right part of src to dest
        while (ptrRight <= right)
            dest[destPtr++] = src[ptrRight++];
    else // right part of src is all copied to dest -> copy left one of left part in src to dest
        while (ptrLeft <= middle)
            dest[destPtr++] = src[ptrLeft++];
}

void _mergePassDesc(int *src, int *dest, int size, int step)
{
    int lastIdx = size - 1;
    int left;
    for (left = 0; left <= lastIdx - 2 * step + 1; left += 2 * step)
        _mergeDesc(src, dest, left, left + step - 1, left + 2 * step - 1);
    if (left + step - 1 < lastIdx)
        _mergeDesc(src, dest, left, left + step - 1, lastIdx);
    else
        for (int j = left; j <= lastIdx; j++)
            dest[j] = src[j];
}

void mergeSort(int *list, int size, int ascend)
{
    int step = 1;
    int *temp = malloc(sizeof(int) * size);
    // call supbrocess
    if (ascend)
    {
        while (step < size)
        {
            _mergePassAsc(list, temp, size, step);
            step *= 2;
            _mergePassAsc(temp, list, size, step);
            step *= 2;
            // to use list as result data (not temp), do mergePass 2 time in a row
        }
    }
    else
    {
        while (step < size)
        {
            _mergePassDesc(list, temp, size, step);
            step *= 2;
            _mergePassDesc(temp, list, size, step);
            step *= 2;
        }
    }
    free(temp);
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
    FILE *fp = fopen("../../Resources/numList.txt", "r");
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
        mergeSort(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_Descend]");
        mergeSort(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}