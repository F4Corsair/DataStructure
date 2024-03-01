#include <stdio.h>
#include <stdlib.h>

/* Utilize max heap(or min heap) structure & sort from popped values
 * 1. Consolidate heap (convert list as a heap)
 * 2. pop data from heap -> fill list backward from last index with popped data
 * if all data popped from heap, then heap list is converted into sorted list
 * time complexity : O(nlogn) & unstable
 */

void swap(int *list, int a, int b)
{
    int temp = list[a];
    list[a] = list[b];
    list[b] = temp;
}

void maxHeapAdjust(int *list, int rootIdx, int lastIdx)
{
    int rootData = list[rootIdx];
    int childIdx = rootIdx * 2 + 1;
    while (childIdx <= lastIdx)
    {
        if ((childIdx < lastIdx) && (list[childIdx] < list[childIdx + 1]))
            childIdx++; // choose bigger element as child
        if (rootData > list[childIdx])
            break; // child is smaller than root(new element)
        else
        {
            list[(childIdx - 1) / 2] = list[childIdx];
            childIdx = childIdx * 2 + 1; // push child element to parent if child is bigger than its parent
        }
    }
    list[(childIdx - 1) / 2] = rootData;
}

void minHeapAdjust(int *list, int rootIdx, int lastIdx)
{
    int rootData = list[rootIdx];
    int childIdx = rootIdx * 2 + 1;
    while (childIdx <= lastIdx)
    {
        if ((childIdx < lastIdx) && (list[childIdx] > list[childIdx + 1]))
            childIdx++; // choose smaller element as child
        if (rootData < list[childIdx])
            break; // child is bigger than root(new element)
        else
        {
            list[(childIdx - 1) / 2] = list[childIdx];
            childIdx = childIdx * 2 + 1; // push child element to parent if child is smaller than its parent
        }
    }
    list[(childIdx - 1) / 2] = rootData;
}

void heapSort(int *list, int size, int ascend)
{
    // call supbrocess
    int step, temp, j;
    if (ascend)
    {
        for (int i = (size - 1) / 2; i >= 0; i--) // heap consolidate
            maxHeapAdjust(list, i, size - 1);
        for (int i = size - 1; i > 0; i--)
        {
            swap(list, 0, i);              // pop data & fill converted list from back
            maxHeapAdjust(list, 0, i - 1); // make heap again
        }
    }
    else
    {
        for (int i = (size - 1) / 2; i >= 0; i--) // heap consolidate
            minHeapAdjust(list, i, size - 1);
        for (int i = size - 1; i > 0; i--)
        {
            swap(list, 0, i);              // pop data & fill converted list from back
            minHeapAdjust(list, 0, i - 1); // make heap again
        }
    }
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
    FILE *fp = fopen("../Resources/numList.txt", "r");
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
        heapSort(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_Descend]");
        heapSort(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}