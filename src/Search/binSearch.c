#include <stdio.h>
#include <stdlib.h>

int int_cmp(const int a, const int b)
{
    return a > b ? 1 : (a < b ? -1 : 0);
}

int binsearch_recursive(int *list, int searchNum, int left, int right)
{
    int center;
    if (left <= right)
    {
        center = (left + right) / 2;
        switch (int_cmp(list[center], searchNum))
        {
        case -1:
            return binsearch_recursive(list, searchNum, center + 1, right);
        case 0:
            return center;
        case 1:
            return binsearch_recursive(list, searchNum, left, center - 1);
        }
    }
    return -1;
}

int binsearch_iterative(int *list, int searchNum, int left, int right)
{
    int center;
    while (left <= right)
    {
        center = (left + right) / 2;
        switch (int_cmp(list[center], searchNum))
        {
        case -1:
            left = center + 1;
            break;
        case 0:
            return center;
        case 1:
            right = center - 1;
        }
    }
    return -1;
}

int main(void)
{
    int numbers[] = {15, 18, 18, 23, 39, 57, 68, 72}; // numbers must be sorted in ascending order
    int searchNum;

    printf("Number to Search : ");
    scanf("%d", &searchNum);

    // int idx = binsearch_iterative(numbers, searchNum, 0, sizeof(numbers) / sizeof(numbers[0]) - 1);
    int idx = binsearch_recursive(numbers, searchNum, 0, sizeof(numbers) / sizeof(numbers[0]) - 1);

    if (idx == -1)
        puts("Failed to search");
    else
        printf("Index of %d in number list : %d\n", searchNum, idx);
}