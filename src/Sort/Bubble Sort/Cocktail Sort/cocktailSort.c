#include <stdio.h>
#include <stdlib.h>

// Cocktail Sort is more optimized version of bubble sort
// repeat going backward & toward, sort it faster than bubble sort
// time complexity : O(n^2) & stable

void swap(int *list, int a, int b)
{
    int temp = list[a];
    list[a] = list[b];
    list[b] = temp;
}

void cocktailSort(int *list, int size, int ascend)
{
    int front = 0;
    int rear = size - 1;
    int lastFront, lastRear;
    if (ascend)
    {
        while (front + 1 < rear) // if [../f/r/..] -> it is sorted. if [../f/ /r/..] is unsorted yer
        {
            lastFront = size - 1;
            lastRear = 0;
            // move back
            for (int i = front; i < rear; i++)
            {
                if (list[i] > list[i + 1])
                {
                    swap(list, i, i + 1);
                    lastRear = i;
                }
            }
            rear = lastRear;

            // move front
            for (int i = rear; i > front; i--)
            {
                if (list[i - 1] > list[i])
                {
                    swap(list, i - 1, i);
                    lastFront = i;
                }
            }
            front = lastFront;
        }
    }
    else
    {
        while (front + 1 < rear)
        {
            lastFront = size - 1;
            lastRear = 0;
            // move back
            for (int i = front; i < rear; i++)
            {
                if (list[i] < list[i + 1])
                {
                    swap(list, i, i + 1);
                    lastRear = i;
                }
            }
            rear = lastRear;

            // move front
            for (int i = rear; i > front; i--)
            {
                if (list[i - 1] < list[i])
                {
                    swap(list, i - 1, i);
                    lastFront = i;
                }
            }
            front = lastFront;
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
        cocktailSort(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_Descend]");
        cocktailSort(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}