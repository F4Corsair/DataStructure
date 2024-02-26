#include <stdio.h>
#include <stdlib.h>

void swap(int *list, int a, int b)
{
    int temp = list[a];
    list[a] = list[b];
    list[b] = temp;
}

void bubbleSortOptimized(int *list, int size, int ascend)
{
    int rear = size - 1;
    if (ascend)
    {
        while (rear > 0)
        {
            int lastSwapIdx = 0;
            for (int i = 0; i < rear; i++)
                if (list[i] > list[i + 1])
                {
                    swap(list, i, i + 1);
                    lastSwapIdx = i;
                }
            rear = lastSwapIdx;
        }
    }
    else
    {
        while (rear > 0)
        {
            int lastSwapIdx = 0;
            for (int i = 0; i < rear; i++)
                if (list[i] < list[i + 1])
                {
                    swap(list, i, i + 1);
                    lastSwapIdx = i;
                }
            rear = lastSwapIdx;
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
        bubbleSortOptimized(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_Descend]");
        bubbleSortOptimized(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}