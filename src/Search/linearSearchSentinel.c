#include <stdio.h>
#include <stdlib.h>

// linear search using sentinel method

int search(int *list, int size, int key)
{
    int i;
    list[size] = key;
    while (1)
    {
        if (list[i] == key)
            break;
        i++;
    }

    return i == size ? -1 : i;
}

int main(void)
{
    // you must prepare list (or allocate) which has 1 free space for sentinel
    int numbers[9] = {15, 18, 18, 23, 39, 57, 68, 72}; // you don't need to sort
    int searchNum;

    printf("Number to Search : ");
    scanf("%d", &searchNum);

    int idx = search(numbers, sizeof(numbers), searchNum);

    if (idx == -1)
        puts("Failed to search");
    else
        printf("Index of %d in number list : %d\n", searchNum, idx);
}