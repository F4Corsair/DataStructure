#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* sort about radix(base), starting from LSD or MSD will determine its sorting order
 * if you sort about 10 base(radix), each digit in same position will be key of each element
 * radix sort commonly applied to sort intger or english words in lexicographic order(26 radix) -> you must consider its length
 * in application, we can sort poker card about shape first & sort about face number when they have same shape
 * LSD(Least Significant Digit) radix sort : keys in same length sorted lexicographically -> stable
 * MSD(Most Significant Digit) radix sort : suit for string sort or fixed length integer -> unstable
 * time complexity : O(nw) such that n : # of keys, w : key length
 * this is non-comparative sorting algortihm
 */

int getMaxValue(int *list, int size)
{
    int max = list[0];
    for (int i = 1; i < size; i++)
        if (list[i] > max)
            max = list[i];
    return max;
}

void countSortAsc(int *list, int size, int exp)
{
    int *sorted = malloc(sizeof(int) * size);
    int count[10] = {0};

    for (int i = 0; i < size; i++) // count occurence of number about exp digit
        count[(list[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1]; // calculate endpoint of each number
    for (int i = size - 1; i >= 0; i--)
    {
        int digitNumber = (list[i] / exp) % 10;
        sorted[--count[digitNumber]] = list[i];
    }
    for (int i = 0; i < size; i++)
        list[i] = sorted[i];
    free(sorted);
}

void countSortDesc(int *list, int size, int exp)
{
    int *sorted = malloc(sizeof(int) * size);
    int count[10] = {0};

    for (int i = 0; i < size; i++) // count occurence of number about exp digit
        count[(list[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1]; // calculate endpoint of each number
    for (int i = 0; i < size; i++)
    { // to save its stability, list traverse direction is inversed
        int val = count[(list[i] / exp) % 10]--;
        sorted[size - val] = list[i];
    }
    for (int i = 0; i < size; i++)
        list[i] = sorted[i];
    free(sorted);
}

void radixSort(int *list, int size, int asc)
{
    int max = getMaxValue(list, size);
    // starting from LSD
    if (asc)
    {
        for (int exp = 1; max / exp > 0; exp *= 10)
            countSortAsc(list, size, exp);
    }
    else
    {
        for (int exp = 1; max / exp > 0; exp *= 10)
            countSortDesc(list, size, exp);
    }
}

void printList(int *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%5d ", list[i]);
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
        puts("[Sorted_LSD_Ascend]");
        radixSort(numList, readSize, 1);
        printList(numList, readSize);
        puts("[Sorted_LSD_Descend]");
        radixSort(numList, readSize, 0);
        printList(numList, readSize);
        free(numList);

        fscanf(fp, " %d", &readSize);
    }
    fclose(fp);
}