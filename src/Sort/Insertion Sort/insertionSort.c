#include <stdio.h>
#include <stdlib.h>

// while increasing range, find new item's proper place
// make its place by by push back elements & save it
// time complexity : O(n^2) & stable

void insertionSort(int *list, int size, int ascend)
{
    int temp, j;
    if (ascend)
    {
        for (int i = 1; i < size; i++)
        {
            temp = list[i];
            for (j = i; j > 0 && list[j - 1] > temp; j--)
                list[j] = list[j - 1];
            list[j] = temp;
        }
    }
    else
    {
        for (int i = 1; i < size; i++)
        {
            temp = list[i];
            for (j = i; j > 0 && list[j - 1] < temp; j--)
                list[j] = list[j - 1];
            list[j] = temp;
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
        insertionSort(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_Descend]");
        insertionSort(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}