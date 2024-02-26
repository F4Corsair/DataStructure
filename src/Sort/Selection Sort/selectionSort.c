#include <stdio.h>
#include <stdlib.h>

// find min(max) value in range, swap it to first item in range
// repeat it while decreasing range
// time complexity : O(n^2) & unstable

void swap(int *list, int a, int b)
{
    int temp = list[a];
    list[a] = list[b];
    list[b] = temp;
}

void selectionSort(int *list, int size, int ascend)
{
    if (ascend)
    {
        for (int i = 0; i < size; i++)
        {
            int min = i;
            for (int j = i + 1; j < size; j++)
                if (list[j] < list[min])
                    min = j;
            swap(list, i, min);
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            int min = i;
            for (int j = i + 1; j < size; j++)
                if (list[j] > list[min])
                    min = j;
            swap(list, i, min);
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
        selectionSort(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_Descend]");
        selectionSort(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}