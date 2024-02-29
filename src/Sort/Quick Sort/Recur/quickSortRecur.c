#include <stdio.h>
#include <stdlib.h>

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

void _qSortAscRecur(int *list, int left, int right)
{
    int lptr = left, rptr = right;
    int pivot = list[(lptr + rptr) / 2];
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
    } while (lptr <= rptr); // let lptr & rptr crosses, prevent recursive call domain overlap
    if (left < rptr)
        _qSortAscRecur(list, left, rptr);
    if (lptr < right)
        _qSortAscRecur(list, lptr, right);
}

void _qSortDescRecur(int *list, int left, int right)
{
    int lptr = left, rptr = right;
    int pivot = list[(lptr + rptr) / 2];
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
        _qSortDescRecur(list, left, rptr);
    if (lptr < right)
        _qSortDescRecur(list, lptr, right);
}

void quickSort(int *list, int size, int ascend)
{
    // call supbrocess
    int step, temp, j;
    if (ascend)
        _qSortAscRecur(list, 0, size - 1);
    else
        _qSortDescRecur(list, 0, size - 1);
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