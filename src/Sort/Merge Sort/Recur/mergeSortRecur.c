#include <stdio.h>
#include <stdlib.h>

/* at first, divde full list to multiple sublists wich has only one elements
 * then, merge 2 sublist to one list, iterate this proecess to reduce the number of sublist by half
 * this will continue until only one sublist left
 * time complexity : O(nlogn) & stable
 */

void _mergeSortAscRecur(int *list, int *temp, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        _mergeSortAscRecur(list, temp, left, center);
        _mergeSortAscRecur(list, temp, center + 1, right);

        int readPtr, tempWritePtr = 0, tempReadPtr = 0;
        int writePtr = left;
        for (readPtr = left; readPtr <= center; readPtr++) // copy front part of list to temp
            temp[tempWritePtr++] = list[readPtr];
        while (readPtr <= right && tempReadPtr < tempWritePtr) // re-write list, smaller one go first
            list[writePtr++] = (temp[tempReadPtr] <= list[readPtr]) ? temp[tempReadPtr++] : list[readPtr++];
        while (tempReadPtr < tempWritePtr) // left elements will add to list
            list[writePtr++] = temp[tempReadPtr++];
    }
}

void _mergeSortDescRecur(int *list, int *temp, int left, int right)
{
    if (left < right)
    {
        int center = (left + right) / 2;
        _mergeSortDescRecur(list, temp, left, center);
        _mergeSortDescRecur(list, temp, center + 1, right);

        int readPtr, tempWritePtr = 0, tempReadPtr = 0;
        int writePtr = left;
        for (readPtr = left; readPtr <= center; readPtr++) // copy front part of list to temp
            temp[tempWritePtr++] = list[readPtr];
        while (readPtr <= right && tempReadPtr < tempWritePtr) // re-write list, smaller one go first
            list[writePtr++] = (temp[tempReadPtr] >= list[readPtr]) ? temp[tempReadPtr++] : list[readPtr++];
        while (tempReadPtr < tempWritePtr) // left elements will add to list
            list[writePtr++] = temp[tempReadPtr++];
    }
}

void mergeSort(int *list, int size, int ascend)
{
    int *temp = malloc(sizeof(int) * size);
    // call supbrocess
    if (ascend)
        _mergeSortAscRecur(list, temp, 0, size - 1);
    else
        _mergeSortDescRecur(list, temp, 0, size - 1);
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