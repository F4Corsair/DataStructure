#include <stdio.h>
#include <stdlib.h>

/* Divide & Conquer version of Insetrion Sort
 *divide group by step, [i+step] [i+2*step]... will be a group
 * iterate insertion sort about groups while decreasing step is positive
 * time complexity : O(n^1.25) & unstable
 */

void shellSort(int *list, int size, int ascend)
{
    int step, temp, j;
    if (ascend)
    {
        for (step = 1; step < size / 9; step = step * 3 + 1)
            ;                       // set proper(efficient) initial step size
        for (; step > 0; step /= 3) // sort with decreasing
            for (int i = step; i < size; i++)
            {
                temp = list[i];
                for (j = i - step; j >= 0 && list[j] > temp; j -= step)
                    list[j + step] = list[j];
                list[j + step] = temp;
            }
    }
    else
    {
        for (step = 1; step < size / 9; step = step * 3 + 1)
            ;                       // set proper(efficient) initial step size
        for (; step > 0; step /= 3) // sort with decreasing
            for (int i = step; i < size; i++)
            {
                temp = list[i];
                for (j = i - step; j >= 0 && list[j] < temp; j -= step)
                    list[j + step] = list[j];
                list[j + step] = temp;
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
        shellSort(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_Descend]");
        shellSort(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}